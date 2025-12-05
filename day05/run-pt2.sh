#!/usr/bin/env bash

cd src
cargo run --release --bin p2 --quiet
cargo clean --quiet
