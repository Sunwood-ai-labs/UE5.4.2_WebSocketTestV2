

<p align="center">
<img src="https://huggingface.co/datasets/MakiAi/IconAssets/resolve/main/UE54Websoket.png" width="100%">
<br>
<h1 align="center">UE5.4.2 WebSocket</h1>
<h2 align="center">

<br>
<a href="https://github.com/Sunwood-ai-labs/UE5.4.2_WebSocketTestV2" title="Go to GitHub repo"><img src="https://img.shields.io/static/v1?label=UE5.4.2_WebSocketTestV2&message=Sunwood-ai-labs&color=blue&logo=github"></a>
<img alt="GitHub Repo stars" src="https://img.shields.io/github/stars/Sunwood-ai-labs/UE5.4.2_WebSocketTestV2">
<a href="https://github.com/Sunwood-ai-labs/UE5.4.2_WebSocketTestV2"><img alt="forks - Sunwood-ai-labs" src="https://img.shields.io/github/forks/UE5.4.2_WebSocketTestV2/Sunwood-ai-labs?style=social"></a>
<a href="https://github.com/Sunwood-ai-labs/UE5.4.2_WebSocketTestV2"><img alt="GitHub Last Commit" src="https://img.shields.io/github/last-commit/Sunwood-ai-labs/UE5.4.2_WebSocketTestV2"></a>
<a href="https://github.com/Sunwood-ai-labs/UE5.4.2_WebSocketTestV2"><img alt="GitHub Top Language" src="https://img.shields.io/github/languages/top/Sunwood-ai-labs/UE5.4.2_WebSocketTestV2"></a>
<img alt="GitHub Release" src="https://img.shields.io/github/v/release/Sunwood-ai-labs/UE5.4.2_WebSocketTestV2?color=red">
<img alt="GitHub Tag" src="https://img.shields.io/github/v/tag/Sunwood-ai-labs/UE5.4.2_WebSocketTestV2?sort=semver&color=orange">
<img alt="GitHub Actions Workflow Status" src="https://img.shields.io/github/actions/workflow/status/Sunwood-ai-labs/UE5.4.2_WebSocketTestV2/publish-to-pypi.yml">
<br>
<p align="center">
  <a href="https://hamaruki.com/"><b>[🌐 Website]</b></a> •
  <a href="https://github.com/Sunwood-ai-labs"><b>[🐱 GitHub]</b></a>
  <a href="https://x.com/hAru_mAki_ch"><b>[🐦 Twitter]</b></a> •
  <a href="https://hamaruki.com/tag/UE5.4.2_WebSocketTestV2/"><b>[🍀 Official Blog]</b></a>
</p>

</h2>

</p>



これは、Unreal Engine 5.4.2 で C++ と Python を WebSocket で通信させるサンプルプロジェクトです。初心者でも理解できるように、丁寧な説明とサンプルコードを提供しています。



## 概要

このプロジェクトでは、以下の機能を実装しています。

- Unreal Engine 5.4.2 の C++ プロジェクトで WebSocket クライアントを実装
- Python で WebSocket サーバーを実装
- キャラクターが特定のキー（E キー）を押すと、WebSocket でメッセージが送信される
- サーバーはメッセージを受信し、応答を返す
- クライアントとサーバーの接続状態がログに記録される

## 動作要件

- Unreal Engine 5.4.2
- Python 3.x
- Python の `websockets` ライブラリ

## セットアップ

1. このリポジトリをクローンまたはダウンロードします。

2. Unreal Engine 5.4.2 でプロジェクトを開きます。

3. Python の依存関係をインストールします。

```bash
pip install websockets loguru tqdm
```

## 使用方法

1. `websocket_server.py` を実行して、WebSocket サーバーを起動します。

```bash
python websocket_server.py
```

2. Unreal Editor でプロジェクトを開き、プレイボタンを押してゲームを開始します。

3. ゲーム内でキャラクターを操作し、`E` キーを押すと、WebSocket でメッセージが送信されます。

4. サーバー側のコンソールで、受信したメッセージと現在の接続数が表示されます。

5. Unreal Engine 側では、送信したメッセージと受信したメッセージがデバッグメッセージとして表示されます。

## ファイル構成

- `WebSocketTestV2.uproject`: Unreal Engine プロジェクトファイル
- `Source/WebSocketTestV2/`: C++ のソースコードフォルダ
  - `WebSocketTestGameInstance.h/.cpp`: WebSocket 接続を管理する GameInstance クラス
  - `WebSocketTestV2Character.h/.cpp`: キャラクターの入力処理と WebSocket メッセージ送信を行うクラス
- `websocket_server.py`: Python の WebSocket サーバーのソースコード

## トラブルシューティング

- WebSocket 接続がうまくいかない場合は、ファイアウォールの設定を確認してください。
- Python の依存関係が正しくインストールされていることを確認してください。
- Unreal Engine プロジェクトのコンパイルエラーが発生した場合は、Visual Studio の出力ウィンドウでエラーメッセージを確認してください。

## 開発用

```bash
sourcesage --mode DocuMind --docuMind-model "gemini/gemini-1.5-pro-latest" --docuMind-db ".SourceSageAssets\DOCUMIND\Repository_summary.md" --docuMind-release-report ".SourceSageAssets\RELEASE_REPORT\Report_v0.2.0.md"  --docuMind-changelog ".SourceSageAssets\Changelog\CHANGELOG_release_0.2.0.md"  --docuMind-output ".SourceSageAssets/DOCUMIND/RELEASE_NOTES_v0.2.0.md"  --docuMind-prompt-output ".SourceSageAssets/DOCUMIND/_PROMPT_v0.2.0.md"  --repo-name "UE5.4.2 WebSocket" --repo-version "v0.2.0"
```

## 貢献

このプロジェクトへの貢献を歓迎します。バグ報告や機能リクエストがある場合は、Issueを作成してください。プルリクエストも大歓迎です。

## ライセンス

このプロジェクトは MIT ライセンスの下で公開されています。詳細については、`LICENSE` ファイルを参照してください。

## 参考リソース

- [Unreal Engine ドキュメント](https://docs.unrealengine.com/ja/index.html)
- [Python WebSocket ライブラリ - websockets](https://websockets.readthedocs.io/en/stable/)
- [YouTube チュートリアル動画 - UE4 C++ WebSocket](https://www.youtube.com/watch?v=l9TTmtDBTWY&t=659s)
- [YouTube チュートリアル動画 - Python WebSocket Server](https://www.youtube.com/watch?v=O-3PNiTHlE0)

上記のREADMEは、初心者にも分かりやすいように、プロジェクトの概要、セットアップ方法、使用方法、ファイル構成、トラブルシューティング、貢献方法、ライセンス、参考リソースなどを丁寧に説明しています。サンプルコードや具体的な手順を示すことで、初心者でもプロジェクトを理解し、実行できるようになっています。