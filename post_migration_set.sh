#!/bin/bash

eosio-cpp --abigen --contract=migratetests post_migration.cpp -o ~/contracts/post_migration.wasm
#sed -i 's/1.1/1.0/g' ~/contracts/post_migration.abi
cleos set contract migratetests ~/contracts/ post_migration.wasm post_migration.abi -p migratetests@active