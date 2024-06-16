#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <string>

using namespace std;
using namespace sql;

struct Aluno {
    string nome;
    string data_nascimento;
    int id_email;
    int id_endereco;
    int id_telefone;
};

struct Professor {
    string nome;
    int salario;
    int id_email;
    int id_endereco;
    int id_telefone;
};

struct Turma {
    int quantidade_alunos;
    int sala_aula;
    int id_curso;
    int id_professor;
};

#pragma region Professor

void createProfessor(Connection* con, Professor prof) {
    PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Professor(nome, salario, id_email, id_endereco, id_telefone) VALUES (?, ?, ?, ?, ?)");
    pstmt->setString(1, prof.nome);
    pstmt->setInt(2, prof.salario);
    pstmt->setInt(3, prof.id_email);
    pstmt->setInt(4, prof.id_endereco);
    pstmt->setInt(5, prof.id_telefone);
    pstmt->executeUpdate();
    delete pstmt;
}

void readProfessor(Connection* con) {
    Statement* stmt = con->createStatement();
    ResultSet* res = stmt->executeQuery("SELECT * FROM Professor");
    while (res->next()) {
        cout << "ID: " << res->getInt("id") << ", Nome: " << res->getString("nome") << ", Salário: " << res->getInt("salario") << endl;
    }
    delete res;
    delete stmt;
}

void updateProfessor(Connection* con, int id, float salario_novo) {
    PreparedStatement* pstmt = con->prepareStatement("UPDATE Professor SET salario = ? WHERE id = ?");
    pstmt->setInt(1, salario_novo);
    pstmt->setInt(2, id);
    pstmt->executeUpdate();
    delete pstmt;
}

void deleteProfessor(Connection* con, int id) {
    PreparedStatement* pstmt = con->prepareStatement("DELETE FROM Professor WHERE id = ?");
    pstmt->setInt(1, id);
    pstmt->executeUpdate();
    delete pstmt;
}

#pragma endregion Professor

#pragma region Aluno

void createAluno(Connection* con, Aluno aluno) {
    PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Aluno(nome, data_nascimento, id_email, id_endereco, id_telefone) VALUES (?, ?, ?, ?, ?)");
    pstmt->setString(1, aluno.nome);
    pstmt->setString(2, aluno.data_nascimento);
    pstmt->setInt(3, aluno.id_email);
    pstmt->setInt(4, aluno.id_endereco);
    pstmt->setInt(5, aluno.id_telefone);
    pstmt->executeUpdate();
    delete pstmt;
}

void readAluno(Connection* con) {
    Statement* stmt = con->createStatement();
    ResultSet* res = stmt->executeQuery("SELECT * FROM Aluno");
    while (res->next()) {
        cout << "ID: " << res->getInt("id") << ", Nome: " << res->getString("nome") << ", Data de Nascimento: " << res->getString("data_nascimento") << endl;
    }
    delete res;
    delete stmt;
}

void updateAluno(Connection* con, int id, string new_name) {
    PreparedStatement* pstmt = con->prepareStatement("UPDATE Aluno SET nome = ? WHERE id = ?");
    pstmt->setString(1, new_name);
    pstmt->setInt(2, id);
    pstmt->executeUpdate();
    delete pstmt;
}

void deleteAluno(Connection* con, int id) {
    PreparedStatement* pstmt = con->prepareStatement("DELETE FROM Aluno WHERE id = ?");
    pstmt->setInt(1, id);
    pstmt->executeUpdate();
    delete pstmt;
}

#pragma endregion Aluno

#pragma region Turma

void createTurma(Connection* con, Turma turma) {
    PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Turma(quantidade_alunos, sala_aula, id_curso, id_professor) VALUES (?, ?, ?, ?)");
    pstmt->setInt(1, turma.quantidade_alunos);
    pstmt->setInt(2, turma.sala_aula);
    pstmt->setInt(3, turma.id_curso);
    pstmt->setInt(4, turma.id_professor);
    pstmt->executeUpdate();
    delete pstmt;
}

void readTurma(Connection* con) {
    Statement* stmt = con->createStatement();
    ResultSet* res = stmt->executeQuery("SELECT * FROM Turma");
    while (res->next()) {
        cout << "ID: " << res->getInt("id") << ", Quantidade de Alunos: " << res->getInt("quantidade_alunos") << ", Sala de Aula: " << res->getInt("sala_aula") << endl;
    }
    delete res;
    delete stmt;
}

void updateTurma(Connection* con, int id, int new_quantity) {
    PreparedStatement* pstmt = con->prepareStatement("UPDATE Turma SET quantidade_alunos = ? WHERE id = ?");
    pstmt->setInt(1, new_quantity);
    pstmt->setInt(2, id);
    pstmt->executeUpdate();
    delete pstmt;
}

void deleteTurma(Connection* con, int id) {
    PreparedStatement* pstmt = con->prepareStatement("DELETE FROM Turma WHERE id = ?");
    pstmt->setInt(1, id);
    pstmt->executeUpdate();
    delete pstmt;
}

#pragma endregion Turma

int menu1() {
    int op;
    do {
        cout << "\n\t[1] - Aluno"
            << "\n\t[2] - Professor"
            << "\n\t[3] - Turma" << endl
            << "\nEscolha uma opcao do menu: ";
        cin >> op;
    } while (op < 1 || op > 3);
    return op;
}

int menu2() {
    int op;
    do {
        cout << "\n\t[1] - Cadastrar dados"
            << "\n\t[2] - Atualizar dados"
            << "\n\t[3] - Ver dados"
            << "\n\t[4] - Deletar dados" << endl
            << "\nEscolha uma opcao do menu: ";
        cin >> op;
    } while (op < 1 || op > 4);
    return op;
}

int main()
{
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    // Conectar ao banco de dados
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "master");  // substitua "root" e "password" por seu usuário e senha
    con->setSchema("escola_ingles");

    int escolha, op;

    while (true) {
        escolha = menu1();

        switch (escolha)
        {
        case 1:
            op = menu2();
            switch (op)
            {
            case 1: {
                Aluno aluno;
                cout << "Digite o nome do aluno: ";
                cin >> aluno.nome;
                cout << "Digite a data de nascimento do aluno (YYYY-MM-DD): ";
                cin >> aluno.data_nascimento;
                cout << "Digite o id do email: ";
                cin >> aluno.id_email;
                cout << "Digite o id do endereco: ";
                cin >> aluno.id_endereco;
                cout << "Digite o id do telefone: ";
                cin >> aluno.id_telefone;
                createAluno(con, aluno);
                break;
            }
            case 2: {
                int id;
                string new_name;
                cout << "Digite o id do aluno a ser atualizado: ";
                cin >> id;
                cout << "Digite o novo nome: ";
                cin >> new_name;
                updateAluno(con, id, new_name);
                break;
            }
            case 3:
                readAluno(con);
                break;
            case 4: {
                int id;
                cout << "Digite o id do aluno a ser deletado: ";
                cin >> id;
                deleteAluno(con, id);
                break;
            }
            }
            break;
        case 2:
            op = menu2();
            switch (op)
            {
            case 1: {
                Professor prof;
                cout << "Digite o nome do professor: ";
                cin >> prof.nome;
                cout << "Digite o salario do professor: ";
                cin >> prof.salario;
                cout << "Digite o id do email: ";
                cin >> prof.id_email;
                cout << "Digite o id do endereco: ";
                cin >> prof.id_endereco;
                cout << "Digite o id do telefone: ";
                cin >> prof.id_telefone;
                createProfessor(con, prof);
                break;
            }
            case 2: {
                int id;
                float salario_novo;
                cout << "Digite o id do professor a ser atualizado: ";
                cin >> id;
                cout << "Digite o novo salario: ";
                cin >> salario_novo;
                updateProfessor(con, id, salario_novo);
                break;
            }
            case 3:
                readProfessor(con);
                break;
            case 4: {
                int id;
                cout << "Digite o id do professor a ser deletado: ";
                cin >> id;
                deleteProfessor(con, id);
                break;
            }
            }
            break;
        case 3:
            op = menu2();
            switch (op)
            {
            case 1: {
                Turma turma;
                cout << "Digite a quantidade de alunos: ";
                cin >> turma.quantidade_alunos;
                cout << "Digite a sala de aula: ";
                cin >> turma.sala_aula;
                cout << "Digite o id do curso: ";
                cin >> turma.id_curso;
                cout << "Digite o id do professor: ";
                cin >> turma.id_professor;
                createTurma(con, turma);
                break;
            }
            case 2: {
                int id, new_quantity;
                cout << "Digite o id da turma a ser atualizada: ";
                cin >> id;
                cout << "Digite a nova quantidade de alunos: ";
                cin >> new_quantity;
                updateTurma(con, id, new_quantity);
                break;
            }
            case 3:
                readTurma(con);
                break;
            case 4: {
                int id;
                cout << "Digite o id da turma a ser deletada: ";
                cin >> id;
                deleteTurma(con, id);
                break;
            }
            }
            break;
        }
    }

    delete con;
    return 0;
}
