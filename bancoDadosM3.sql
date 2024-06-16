CREATE SCHEMA escola_ingles;
use escola_ingles;
-- DROP escola_ingles;


CREATE TABLE Professor (
    id INT PRIMARY KEY auto_increment,
    nome VARCHAR(20) NOT NULL,
    salario INT NOT NULL,
    id_email INT NOT NULL,
    id_endereco INT NOT NULL,
    id_telefone INT NOT NULL,
    FOREIGN KEY (id_email) REFERENCES Email(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (id_endereco) REFERENCES Endereco(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (id_telefone) REFERENCES Telefone(id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Aluno (
    id INT PRIMARY KEY auto_increment,
    nome VARCHAR(20) NOT NULL,
    data_nascimento DATE NOT NULL,
    id_email INT NOT NULL,
    id_endereco INT NOT NULL,
    id_telefone INT NOT NULL,
    FOREIGN KEY (id_email) REFERENCES Email(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (id_endereco) REFERENCES Endereco(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (id_telefone) REFERENCES Telefone(id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Turma (
    id INT PRIMARY KEY auto_increment,
    quantidade_alunos INT,
    sala_aula INT NOT NULL,
    id_curso INT NOT NULL,
    id_professor INT NOT NULL,
    FOREIGN KEY (id_aluno) REFERENCES Aluno(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (id_turma) REFERENCES Turma(id) ON UPDATE CASCADE ON DELETE CASCADE
);
