# DHT11_demo
The 8051 demo of DHT11 module. Rewrite and add more comments (based on the official one).

## Getting started

### Build

Open with Keil, check `Options for Target`, open the `Output` tab, make sure `Create HEX File` is checked.

Then `Build`

### Deploying

Note: This demo is designed for STC 12C5A60S2. Some changes might be needed if you're using other 8051 MCU.

LCD1602 Connection: RS--P0.7, RW--P0.6, E--P0.5, DB0--P2.0

DHT11 Connection : DAT--P1.1

