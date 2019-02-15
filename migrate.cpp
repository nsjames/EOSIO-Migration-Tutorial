#include <eosiolib/eosio.hpp>

using namespace eosio;

CONTRACT migratetests : contract {

private:

    // This is the struct we are migrating TO
    TABLE new_struct {
        uint64_t    id;
        name        payer;

        // WE ARE ADDING THIS PROPERTY
        std::string new_property = "migrated";

        uint64_t    primary_key() const { return id; }
    };

    // This is the struct that we are migrating FROM
    TABLE old_struct {
        uint64_t    id;
        name        payer;

        // WE ARE REMOVING THIS PROPERTY
        uint64_t    old_property;

        uint64_t    primary_key() const { return id; }

        /***
         * We are creating a simple method to take the old
         * structure and migrate it into the new one.
         * This allows granular mutability to do things like
         * changing properties based on new structures.
         */
        new_struct  toNew() const {
            new_struct n;
            n.id = id;
            n.payer = payer;
            return n;
        }
    };

    // This is the table that we will be migrating TO.
    // It is currently empty and will be filled with the new data
    // ----------------------------------------------------------
    // When you are done migrating you will change the name to "usedtable"
    // so that the rest of your contract's code uses the new table instead of the old.
    typedef eosio::multi_index<"newtable"_n, new_struct> NewTable;

    // UNCOMMENT AFTER MIGRATION
    // You will also need to remove all migration code to clear references.
//    typedef eosio::multi_index<"usedtable"_n, new_struct> UsedTable;


    // This is the table we will be migrating FROM.
    typedef eosio::multi_index<"usedtable"_n, old_struct> UsedTable;


    UsedTable usedTable;
    NewTable newTable;

public:
    using contract::contract;
    migratetests(name receiver, name code,  datastream<const char*> ds):contract(receiver, code, ds),
        usedTable(_self, _self.value),
        newTable(_self,_self.value){}

    /***
     * Migrates the old table to a new one with structure changes.
     * ------------------------------------
     * Keep running this method until it asserts.
     * @return
     */
    ACTION migrate(){
        // Just asserting if no more rows to migrate.
        eosio_assert(usedTable.begin() != usedTable.end(), "There are no rows left to migrate");

        // You can change the amount of rows to migrate per call
        // based on the data in your contract as it will costs different
        // amounts of CPU depending on the structures.
        int maxPerCall = 10;

        uint8_t i = 0;
        while(usedTable.begin() != usedTable.end() && i < 10){
            // Getting a row;
            auto itr = --usedTable.end();

            // Inserting the row into the new table.
            newTable.emplace(itr->payer, [&](auto& row){
                row = itr->toNew();
            });

            // Removing the old row.
            usedTable.erase(itr);

            i++;
        }

    }

    /***
     * Just inserts a dummy row into the old data table.
     * Run multiple times to insert more rows.
     * @return
     */
    ACTION dummyrows(){
        usedTable.emplace(_self, [&](auto& row){
            row.id = usedTable.available_primary_key();
            row.payer = _self;
            row.old_property = 1;
        });
    }


};

EOSIO_DISPATCH( migratetests, (migrate)(dummyrows) )