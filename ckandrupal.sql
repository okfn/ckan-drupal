CREATE DATABASE ckandrupal;
BEGIN
CREATE ROLE ckandrupal with PASSWORD 'ckandrupal' LOGIN;
GRANT ALL PRIVILEGES ON DATABASE ckandrupal to ckandrupal;
COMMIT
