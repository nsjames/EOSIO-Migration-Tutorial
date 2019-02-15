#!/bin/bash

echo "-------------------"
echo "UsedTable"
cleos get table migratetests migratetests usedtable
echo ""
echo ""

echo "NewTable"
cleos get table migratetests migratetests newtable
echo ""
echo ""

echo "-------------------"