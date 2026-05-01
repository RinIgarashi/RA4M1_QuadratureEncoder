# RA4M1_QuadratureEncoder

Renesas RA4M1 の GPT 位相計数機能を使って、ロータリーエンコーダをカウントするためのライブラリです。

## 対応環境

- Arduino IDE
- PlatformIO
- 対象ボード: Renesas RA4M1 搭載ボード

## API

### QuadratureEncoder(uint8_t timer_ch, uint16_t pinA, uint16_t pinB)

`timer_ch` は GPT0 から GPT7 までのチャネル番号です。

`pinA` と `pinB` は `105` や `PORT_PIN(1, 5)` のような RA4M1 のポート/ピン表記を指定します。

### begin()

GPT と入出力ピンを初期化し、カウントを開始します。

### read()

現在のカウント値を `int32_t` で返します。

### write(int32_t value)

カウンタ値を指定値に設定します。

## 注意事項

- ピン番号は RA4M1 のポート表記に合わせて指定してください。
- 使用する GPT チャネルとピンの組み合わせは、ボードのピン配置に依存します。
- 初期化前に対象ピンが他の機能で使われていないことを確認してください。
