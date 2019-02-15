#include <eosiolib/eosio.hpp>

using namespace eosio;

CONTRACT migratetests : contract {

private:

    // This is the struct we are migrating TO
    TABLE new_struct {
        uint64_t    id;
        name        payer;
        std::string new_property = "migrated";

        uint64_t    primary_key() const { return id; }
    };

    typedef eosio::multi_index<"usedtable"_n, new_struct> UsedTable;


    UsedTable usedTable;

public:
    using contract::contract;
    migratetests(name receiver, name code,  datastream<const char*> ds):contract(receiver, code, ds),
        usedTable(_self, _self.value){}

    /***
     * Just inserts a dummy row into the old data table.
     * Run multiple times to insert more rows.
     * @return
     */
    ACTION dummyrows(){
        usedTable.emplace(_self, [&](auto& row){
            row.id = usedTable.available_primary_key();
            row.payer = _self;
            row.new_property = "hello world";
        });
    }


};

EOSIO_DISPATCH( migratetests, (dummyrows) )