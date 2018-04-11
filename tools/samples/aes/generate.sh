#!/bin/sh

# This program generates the samples for testing with AES using OpenSSL

generate() {
	openssl $1 -e -in CRYPTOSAMPLES_KEY256.dat -out CRYPTOSAMPLES_KEY256-$1.enc -K $2 -nopad
	openssl $1 -d -in CRYPTOSAMPLES_KEY256-$1.enc -out CRYPTOSAMPLES_KEY256-$1.dec -K $2 -nopad
	echo "$1 Dec (key:$2):"
	cat CRYPTOSAMPLES_KEY256-$1.dec | xxd -g32 -c32
	echo "$1 Enc (key:$2):"
	cat CRYPTOSAMPLES_KEY256-$1.enc | xxd -g32 -c32
	echo "--"
}

generate aes-128-ecb 0123456789ABCEDF
generate aes-256-ecb 0123456789ABCEDF0123456789ABCEDF

