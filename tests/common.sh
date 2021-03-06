#!/bin/bash

function wait_for_network_namespace {
    # Wait that the namespace is ready.
    COUNTER=0
    while [ $COUNTER -lt 10 ]; do
        if nsenter --preserve-credentials -U -n --target=$1 true; then
            break
        else
            sleep 0.5
        fi
        let COUNTER=COUNTER+1
    done
}

function wait_for_network_device {
    # Wait that the device appears.
    COUNTER=0
    while [ $COUNTER -lt 20 ]; do
        if nsenter --preserve-credentials -U -n --target=$1 ip addr show $2; then
            break
        else
            sleep 0.5
        fi
        let COUNTER=COUNTER+1
    done
}

function wait_process_exits {
    COUNTER=0
    while [ $COUNTER -lt 20 ]; do
        if  kill -0 $1; then
            sleep 0.5
        else
            break
        fi
        let COUNTER=COUNTER+1
    done
}

function wait_for_ping_connectivity {
    COUNTER=0
    while [ $COUNTER -lt 20 ]; do
        if nsenter --preserve-credentials -U -n --target=$1 ping -c 1 -w 1 $2; then
            break
        else
            sleep 0.5
        fi
        let COUNTER=COUNTER+1
    done
}
