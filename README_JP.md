# RA4M1_QuadratureEncoder

Renesas RA4M1 マイコンの GPT 位相カウンタ機能を利用してエンコーダをカウントするための Arduino ライブラリです。

[English](README.md)

## フレームワークとデバイス

- Arduino IDE / PlatformIO
- Renesas RA4M1 搭載ボード\
	(例: Arduino UNO R4 Minima, Arduino UNO R4 WiFi)

## 対応ピン表

| GPT CH | PinA / PinB | R4-Minima ピン | R4-WiFi ピン |
|---:|---|---|---|
| 0 (32bit) | P107 / P106 | D7 / D6 | D5 / D4 |
| 1 (32bit) | P105 / P104 | D2, D11 / D3, D12 | D3 / D2 |
| 2 (16bit) | P103 / P102 | D4 / D5 | D10 / D13 |
| 3 (16bit) | P111 / P112 | D13 / D10 | D6 / D7 |
| 4 (16bit) | P302 / P301 | D1 / D0 | D1 / D0 |
| 5 (16bit) | P100 / P101 | D15 / D14 | D15 / D14 |
| 6 (16bit) | P411 / P410 | - / - | D11 / D12 |
| 7 (16bit) | P304 / P303 | D8 / D9 | D8 / D9 |

<details>
<summary>Arduino 公式ボードのピン配置</summary>

<figure>
  <img src="docs/img/R4-Minima_pinout.png" alt="Arduino UNO R4 Minima ピン配置">
  <figcaption>Arduino UNO R4 Minima</figcaption>
</figure>

<figure>
  <img src="docs/img/R4-WiFi_pinout.png" alt="Arduino UNO R4 WiFi ピン配置">
  <figcaption>Arduino UNO R4 WiFi</figcaption>
</figure>

</details>

## API

### `QuadratureEncoder(uint8_t timer_ch, uint16_t pinA, uint16_t pinB)`

指定した GPT チャネル用のエンコーダインスタンスを生成します。

- `timer_ch`: GPT のチャネル番号 **(0〜7)**
- `pinA`, `pinB`: RA4M1 のポート/ピン表記（例: `105` または `PORT_PIN(1, 5)`）

### `begin()`

GPT と I/O ピンを初期化し、カウントを開始します。

### `read()`

現在のカウント値を `int32_t` で返します。

### `write(int32_t value)`

カウンタを指定値に設定します。

## ⚠️ 免責事項

- **ハードウェアピンの直接操作:**
	ライブラリは指定ピンのレジスタを変更して GTIOCxA/B 機能に設定します。`begin()` 実行後は該当ピンがエンコーダ入力専用になります。
- **他ライブラリとのタイマ競合:**
	使用する GPT チャネルが他のライブラリ（サーボ制御など）と競合しないことを確認してください。
- **ピンマッピングの差異:**
	ボードによって内部ルーティングが異なる場合があります。Minima / WiFi など、ご使用のボードの回路図やデータシートを参照してください。
- **サンプルの扱い:**
	サンプルスケッチは参考用です。配線やエンコーダ仕様（プルアップの要否等）に合わせて調整してください。
- **ピンの事前確認:**
	`begin()` を呼ぶ前に、ターゲットピンが他の周辺機器やライブラリで使用されていないか確認してください。

## ライセンス

このプロジェクトは MIT ライセンスの下で公開されています。詳細については [LICENSE](LICENSE) ファイルをご覧ください。

