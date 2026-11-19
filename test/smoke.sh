#!/bin/sh
# test/smoke.sh —— 起服务、打一组边界请求、任何一条不符就退出非 0
# 用法: sh test/smoke.sh            （用默认路径 ~/b-ubsan/server）
#       sh test/smoke.sh /path/to/server
set -e

SERVER=${1:-$HOME/b-ubsan/server}
PORT=8080
B="http://localhost:$PORT"

# ── 0. 先确认端口没被占（否则测的是旧进程 => 假绿）──
if curl -s -o /dev/null --max-time 1 "$B/api/add?a=1&b=1"; then
    echo "端口 $PORT 已被占用。先 Ctrl+C 关掉手动启动的 server，再跑本脚本。"
    exit 2
fi

# ── 1. 启动被测服务 ──
"$SERVER" &
SRV=$!
trap 'kill $SRV 2>/dev/null || true; wait $SRV 2>/dev/null || true' EXIT
sleep 1

fail=0

# chk <期望的 body> <url>
chk() {
    got=$(curl -s --max-time 5 "$2" || echo "__CURL_FAIL__")
    if [ "$got" != "$1" ]; then
        echo "FAIL $2"
        echo "  want body: $1"
        echo "  got  body: $got"
        fail=1
    fi
}

# code <期望的状态码> <url>
code() {
    got=$(curl -s -o /dev/null -w '%{http_code}' --max-time 5 "$2" || echo "__CURL_FAIL__")
    if [ "$got" != "$1" ]; then
        echo "FAIL $2"
        echo "  want status: $1"
        echo "  got  status: $got"
        fail=1
    fi
}

# ── 2. 用例 ──
chk  '{"result":3}'         "$B/api/add?a=1&b=2"
chk  '{"result":6}'         "$B/api/gcd?a=12&b=18"
chk  '{"result":-0.479426}' "$B/api/sin?a=-.5"

code 400 "$B/api/add?a=9223372036854775807&b=1"
code 400 "$B/api/gcd?a=0&b=0"
code 400 "$B/api/gcd?a=-9223372036854775808&b=1"
code 400 "$B/api/sin?a=."
code 400 "$B/api/sin?a=-"

# ── 3. 汇总 ──
if [ "$fail" -ne 0 ]; then
    echo "---- FAILED ----"
    exit 1
fi
echo "all ok"