#!/bin/bash

#
#
#
#
#

sudo apt-get install build-essential libxml2-dev libxslt-dev wget postgresql libpq-dev git-core python-dev python-psycopg2 python-virtualenv subversion mercurial
virtualenv ckan-drupal
. ckan-drupal/bin/activate
pip install -r ckan-drupal/ckan/requires/lucid_missing.txt -r ckan-drupal/ckan/requires/lucid_conflict.txt -r ckan-drupal/ckan/requires/lucid_present.txt
sudo -u postgres psql --file=ckandrupal.sql
cd ckan-drupal/ckanext-drupal
python setup.py develop
cd ../..
cd ckan-drupal/ckan
paster make-config ckan development.ini
paster db init
python setup.py develop