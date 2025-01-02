CREATE DATABASE db_ticket;

USE db_ticket;

CREATE TABLE ticket(
id_registro int primary key auto_increment,
status_ticket varchar(50) not null,
id_ticket int not null,
nome_solicitante varchar(100) not null,
assunto_ticket varchar(500) not null,
hora_alteração datetime not null
);

ALTER TABLE ticket auto_increment = 1;

SELECT * FROM ticket WHERE 1;
