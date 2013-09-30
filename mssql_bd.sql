{\rtf1\ansi\ansicpg1251\cocoartf1138\cocoasubrtf510
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
\paperw16837\paperh11905\margl1440\margr1440\vieww18520\viewh8400\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural

\f0\fs24 \cf0 DROP TABLE client\
DROP TABLE card\
DROP TABLE contract\
DROP TABLE operation\
\
/*CREATE TYPE TYPE_CARDS AS ENUM ('Berlitz Respect', 'Berlitz Honour', 'Berlitz Silver Member', 'Berlitz Gold Member');\
\uc0\u1042  MS SQL \u1085 \u1077 \u1090  ENUM?\
*/\
\
CREATE TABLE client \
(\
    id integer NOT NULL,\
    surname varchar(50),\
    name varchar(50),\
    middlename varchar(50)\
)\
\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural
\cf0 CREATE TABLE card \
(\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural
\cf0     id integer NOT NULL,\
    id_parent integer,\
    type varchar(20),\
    date_begin datetime,\
    date_end datetime,\
    id_client integer\
)\
\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural
\cf0 CREATE TABLE contract \
(\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural
\cf0     id integer NOT NULL,\
    id_client integer,\
    sum money\
)\
\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural
\cf0 CREATE TABLE operation \
(\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural
\cf0     id_client integer,\
    id_contract integer,\
    id_card integer,\
    date datetime,\
    sum money\
)\
}