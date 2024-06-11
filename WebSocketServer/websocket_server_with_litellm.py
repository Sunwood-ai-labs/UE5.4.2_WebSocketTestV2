from dotenv import load_dotenv
import asyncio
import websockets
import uuid
from loguru import logger
import time
from tqdm import tqdm
from litellm import completion
import os

load_dotenv(verbose=True)

connected_clients = set()

async def generate_response(message):
    response = completion(
        model="gemini/gemini-pro",
        messages=[{"role": "user", "content": message}]
    )
    return response

async def handle_client(websocket, path):
    connection_id = uuid.uuid4()
    client_address = websocket.remote_address
    client_info = f"接続元 IP: {client_address[0]}, ポート: {client_address[1]}"
    
    if connection_id not in connected_clients:
        logger.info(f"クライアント接続: {client_info} (WebSocket ID: {connection_id})")
        connection_info_message = f"サーバーに接続しました。接続情報: {client_info}, WebSocket ID: {connection_id}"
        await websocket.send(connection_info_message)
        logger.info(f"{client_address}に接続情報を送信: {connection_info_message}")
        connected_clients.add(connection_id)

    try:
        async for message in websocket:
            logger.info(f"{client_address}からメッセージを受信 (WebSocket ID: {connection_id}): {message}")
            
            # litellmを使用して応答を生成
            response = await generate_response(message)
            content = response.get('choices', [{}])[0].get('message', {}).get('content')
            
            await websocket.send(content)
            logger.info(f"{client_address}に応答を送信 (WebSocket ID: {connection_id}): {content}")

    except websockets.ConnectionClosed as e:
        logger.info(f"クライアントによる接続切断: {client_info} (WebSocket ID: {connection_id}), コード: {e.code}, 理由: {e.reason}")
        connected_clients.remove(connection_id)

    logger.info(f"クライアント切断: {client_info} (WebSocket ID: {connection_id})")

async def start_server():
    server = await websockets.serve(handle_client, "localhost", 8080)
    logger.info("WebSocketサーバーを ws://localhost:8080 で起動")
    await server.wait_closed()

if __name__ == "__main__":
    logger.add("websocket_server.log", rotation="1 MB", retention="7 days")
    asyncio.run(start_server())