#!/bin/bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./spamid.exe spam 10 ham 10 spam 10 result.txt