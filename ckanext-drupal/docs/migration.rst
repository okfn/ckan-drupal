Database Migration Steps
------------------------

1. Get a dump of a ckan database. e.g::

    pg_dump -f dump.sql ckan

2. Drop and create a clean database::

    dropdb dgu
    createdb dgu

3. If you are have postgis installed on your instance you need to run::

    psql -d dgu -f /usr/share/postgresql/9.0/contrib/postgis-1.5/postgis.sql

4. Load the data::

    psql -d dgu -f dump.sql

5. Make sure database is upto date::

   paster db upgrade

5. Run the migration, change the api-key to a sysadmins key::

   curl http://0.0.0.0:5000/api/action/migrate_data -d '{}' -H "Authorization:api-key"

