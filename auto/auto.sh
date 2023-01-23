#!/bin/bash

# Copyright 2023 Auto Authors

# TODO: Add support for other OSs

if [ -z $1 ]; then
    echo "Usage: ./auto.sh [all|meta|dep|pkg|hook] [--force]"
    exit 1
fi

# Get latest version of auto.sh
if [ ! -z $1 ] && [ $1 == "all" ] || [ $1 == "meta" ]; then
    wget https://raw.githubusercontent.com/tharatau/idea-maze/main/auto/auto.sh -O ${HOME}/auto.sh
fi

if [ ! -z $1 ] && [ $1 == "all" ] || [ $1 == "pkg" ]; then
    # Install packages required by auto.sh
    PKGS=(
        "jq"
        "wget"
        "unzip"
    )

    sudo apt update

    for pkg in "${PKGS[@]}"; do
        sudo apt install $pkg
    done

    # Install packages defined by user
    USR_PKGS=$(jq -r ".pkgs[]" auto.json)

    for pkg in "${USR_PKGS[@]}"; do
        sudo apt install $pkg
    done
fi

if [ ! -z $1 ] && [ $1 == "all" ] || [ $1 == "dep" ]; then

    # Download dependencies
    DEPS=$(jq ".deps[]" auto.json)

    for dep in "${DEPS[@]}"; do
        DEP_NAME=$(jq -r ".name" <<<$dep)
        DEP_DIR=$(jq -r ".dir" <<<$dep)
        DEP_URI=$(jq -r ".uri" <<<$dep)
        DEP_REV=$(jq -r ".rev" <<<$dep)

        if [[ ! -d $DEP_DIR ]]; then
            mkdir -p $DEP_DIR
        fi

        if [[ -d $DEP_DIR/$DEP_NAME ]] && [ ! -z $2 ] && [ $2 == "--force" ]; then
            rm -rf $DEP_DIR/$DEP_NAME
        fi

        if [[ ! -d $DEP_DIR/$DEP_NAME ]]; then
            # TODO: regex uri to check for different types of repos
            wget $DEP_URI/archive/$DEP_REV.zip -O $DEP_DIR/$DEP_NAME.zip
            unzip $DEP_DIR/$DEP_NAME.zip -d $DEP_DIR/$DEP_NAME
            rm -rf $DEP_DIR/$DEP_NAME.zip

            mv $DEP_DIR/$DEP_NAME/**/* $DEP_DIR/$DEP_NAME
            mv $DEP_DIR/$DEP_NAME/**/.* $DEP_DIR/$DEP_NAME
        fi
    done
fi

if [ ! -z $1 ] && [ $1 == "all" ] || [ $1 == "hook" ]; then

    # Build dependencies
    HOOKS=$(jq -r ".hooks[]" auto.json)
    for hook in "${HOOKS[@]}"; do
        HOOK_DIR=$(jq -r ".dir" <<<$hook)
        HOOK_RUN=$(jq -r ".run[]" <<<$hook)

        cd $HOOK_DIR

        for run in "${HOOK_RUN[@]}"; do
            eval "$run"
        done

        cd -
    done
fi
