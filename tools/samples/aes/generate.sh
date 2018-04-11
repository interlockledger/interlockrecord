#!/bin/sh

# This program generates the samples for testing with AES using OpenSSL

# Simple... logic.
CRYPTOSAMPLES_KEY128=53696d706c652e2e2e206c6f6769632e
# Kosh: You have always been here.
CRYPTOSAMPLES_KEY256=4b6f73683a20596f75206861766520616c77617973206265656e20686572652e

generate() {
	openssl $1 -e -in CRYPTOSAMPLES_KEY256.dat -out CRYPTOSAMPLES_KEY256-$1.enc -K $2 -nopad
	openssl $1 -d -in CRYPTOSAMPLES_KEY256-$1.enc -out CRYPTOSAMPLES_KEY256-$1.dec -K $2 -nopad
	echo "$1 Dec (key:$2):"
	cat CRYPTOSAMPLES_KEY256-$1.dec | xxd -g32 -c32
	echo "$1 Enc (key:$2):"
	cat CRYPTOSAMPLES_KEY256-$1.enc | xxd -g32 -c32
	echo "--"
}

printf "Kosh: You have always been here." > CRYPTOSAMPLES_KEY256.dat
generate aes-128-ecb $CRYPTOSAMPLES_KEY128
generate aes-256-ecb $CRYPTOSAMPLES_KEY256

