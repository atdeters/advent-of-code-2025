#!/usr/bin/env bash

cd src
cargo run --release --bin p1 --quiet
cargo clean --quiet
