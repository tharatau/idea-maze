#!/bin/bash

# Copyright 2023 Auto Authors

# Install System dependencies
# TODO: Add support for other OSs
PKGS=(
    "jq"
    "wget"
    "unzip"
)

sudo apt update
for pkg in "${PKGS[@]}"; do
    sudo apt install $pkg
done

USR_PKGS=$(jq -r ".pkgs[]" auto.json)

for pkg in "${USR_PKGS[@]}"; do
    sudo apt install $pkg
done

DEPS=$(jq ".deps[]" auto.json)

for dep in "${DEPS[@]}"; do
    DEP_NAME=$(jq -r ".name" <<<$dep)
    DEP_DIR=$(jq -r ".dir" <<<$dep)
    DEP_URI=$(jq -r ".uri" <<<$dep)
    DEP_REV=$(jq -r ".rev" <<<$dep)

    if [[ ! -d $DEP_DIR ]]; then
        mkdir -p $DEP_DIR
    fi

    # TODO: regex uri to check for different types of repos
    wget $DEP_URI/archive/$DEP_REV.zip -O $DEP_DIR/$DEP_NAME.zip
    unzip $DEP_DIR/$DEP_NAME.zip -d $DEP_DIR/$DEP_NAME
    rm -rf $DEP_DIR/$DEP_NAME.zip

    mv $DEP_DIR/$DEP_NAME/**/* $DEP_DIR/$DEP_NAME
    mv $DEP_DIR/$DEP_NAME/**/.* $DEP_DIR/$DEP_NAME
done
