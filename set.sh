#!/bin/bash

eosio-cpp --abigen --contract=migratetests migrate.cpp -o ~/contracts/migrate.wasm
#sed -i 's/1.1/1.0/g' ~/contracts/migrate.abi
cleos set contract migratetests ~/contracts/ migrate.wasm migrate.abi -p migratetests@active