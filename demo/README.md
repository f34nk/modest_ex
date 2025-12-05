# ModestEx Demo

A standalone demo app to verify modest_ex 2.1.0 installation from hex.pm.

## Prerequisites

- Elixir 1.14+
- Lexbor C library installed (see main README)

## Run

```bash
# From project root
make demo

# Or manually
cd demo
mix deps.get
mix run -e "Demo.run"

# Run all feature demos
mix run -e "Demo.run_all"
```

## What it does

1. Installs modest_ex 2.1.0 from hex.pm
2. Runs the example code from the main README
3. Verifies the output matches expected result
