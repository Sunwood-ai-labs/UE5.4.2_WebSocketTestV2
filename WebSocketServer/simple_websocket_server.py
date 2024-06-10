import asyncio
import websockets
from loguru import logger

async def handle_client(websocket, path):
    client_address = websocket.remote_address
    logger.info(f"Client connected: {client_address}")

    async for message in websocket:
        logger.info(f"Received message from {client_address}: {message}")
        response = f"Server received: {message}"
        await websocket.send(response)
        logger.info(f"Sent response to {client_address}: {response}")

    logger.info(f"Client disconnected: {client_address}")

async def start_server():
    server = await websockets.serve(handle_client, "localhost", 8080)
    logger.info(f"WebSocket server started on ws://localhost:8080")
    await server.wait_closed()

if __name__ == "__main__":
    logger.add("websocket_server.log", rotation="1 MB", retention="7 days")
    asyncio.run(start_server())