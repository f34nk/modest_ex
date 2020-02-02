#!/bin/bash

mix local.hex --force
mix deps.get
mix deps.compile
mix compile