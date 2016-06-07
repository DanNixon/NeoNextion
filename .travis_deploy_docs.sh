#!/bin/bash

if [ "$TRAVIS_PULL_REQUEST" != "false" -o "$TRAVIS_BRANCH" != "master" ];
then
  echo Not publishing documentation.
  exit 0;
fi

git config --global user.email "nobody@nobody.org"
git config --global user.name "Travis CI"

# Publish the PlatformIO library.json
cp library.json docs/html

cd docs/html
git init

git add .
git commit -m "Deploy Doxygen documentation"
git push --force --quiet "https://${GH_TOKEN}@${GH_REF}" master:gh-pages > /dev/null 2>&1
