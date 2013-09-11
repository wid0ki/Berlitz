DROP TYPE IF EXISTS TYPE_CARDS;
DROP TABLE IF EXISTS client;
DROP TABLE IF EXISTS card;
DROP TABLE IF EXISTS contract;
DROP TABLE IF EXISTS operation;

CREATE TYPE TYPE_CARDS AS ENUM ('Berlitz Respect', 'Berlitz Honour', 'Berlitz Silver Member', 'Berlitz Gold Member');

CREATE TABLE client (
    id SERIAL NOT NULL,
    surname TEXT,
    name TEXT,
    middlename TEXT
) WITH (
    oids=false
);

CREATE TABLE card (
    id SERIAL NOT NULL,
    id_parent SERIAL,
    type TYPE_CARDS,
    date_begin DATE NOT NULL,
    date_end DATE,
    id_client SERIAL
) WITH (
    oids=false
);

CREATE TABLE contract (
    id SERIAL NOT NULL,
    id_client SERIAL,
    sum MONEY
) WITH (
    oids=false
);

CREATE TABLE operation (
    id_client SERIAL,
    id_contract SERIAL,
    id_card SERIAL,
    date DATE NOT NULL,
    sum MONEY
) WITH (
oids=false
);
