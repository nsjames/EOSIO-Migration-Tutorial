# EOSIO Table Migration Tutorial


### Setting things up

1) Create an account named `migratetests` on your local `nodeos`.

-----

2) Compile and set the contract using either the `./set.sh` script, or by issuing the following commands.

`eosio-cpp --abigen --contract=migratetests migrate.cpp -o migrate.wasm`

`cleos set contract migratetests ../ migrate.wasm migrate.abi -p migratetests@active`

-----

3) Create some dummy rows using the following command a few times

`cleos push action migratetests dummyrows '[]' -p migratetests`

-----

4) Look at the table data to see which table the data is currently in.

`./tables.sh`

-----

5) Migrate the data using:

`cleos push action migratetests migrate '[]' -p migratetests`

-----

6) Look at the table data again to see how it has changed.

`./tables.sh`



### After you are done.

You can use the `post_migration_set.sh` script or set the `post_migration.cpp` contract manually which
removes all of the migration code and only leaves the new table.
