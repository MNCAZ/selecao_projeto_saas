#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <list>
#include <assert.h>

using namespace std;

/*
 * Esta classe representa cada opção de saque
 * disponível ao efetuar o saque de um determinado
 * valor em um caixa eletrõnico 
 */
class OpcaoSaque
{
private:
    // Atributos
    long int quantidadeNota10Utilizadas;
    long int quantidadeNota20Utilizadas;
    long int quantidadeNota50Utilizadas;
    long int quantidadeNota100Utilizadas;

    long int quantidadeNota10Disponiveis;
    long int quantidadeNota20Disponiveis;
    long int quantidadeNota50Disponiveis;
    long int quantidadeNota100Disponiveis;

    long int resto;
    long int total;

public:
    // Construtor
    OpcaoSaque(long int valor,
               long int qtdNota100Disponiveis,
               long int qtdNota50Disponiveis,
               long int qtdNota20Disponiveis,
               long int qtdNota10Disponiveis)
    {
        quantidadeNota10Disponiveis = qtdNota10Disponiveis;
        quantidadeNota20Disponiveis = qtdNota20Disponiveis;
        quantidadeNota50Disponiveis = qtdNota50Disponiveis;
        quantidadeNota100Disponiveis = qtdNota100Disponiveis;

        quantidadeNota10Utilizadas = 0;
        quantidadeNota20Utilizadas = 0;
        quantidadeNota50Utilizadas = 0;
        quantidadeNota100Utilizadas = 0;

        resto = valor;
        total = valor;
    }

    // Destrutor
    ~OpcaoSaque()
    {
    }

    // Sets
    void setResto(long int rst)
    {
        resto = rst;
    }

    // Increments
    void incrementarQuantidadeNota10Utilizadas(long int quantidade)
    {
        quantidadeNota10Utilizadas += quantidade;
    }

    void incrementarQuantidadeNota120Utilizadas(long int quantidade)
    {
        quantidadeNota20Utilizadas += quantidade;
    }

    void incrementarQuantidadeNota50Utilizadas(long int quantidade)
    {
        quantidadeNota50Utilizadas += quantidade;
    }

    void incrementarQuantidadeNota100Utilizadas(long int quantidade)
    {
        quantidadeNota100Utilizadas += quantidade;
    }

    // Gets
    long int getQuantidadeNota10Disponiveis()
    {
        return quantidadeNota10Disponiveis;
    }

    long int getQuantidadeNota20Disponiveis()
    {
        return quantidadeNota20Disponiveis;
    }

    long int getQuantidadeNota50isponiveis()
    {
        return quantidadeNota50Disponiveis;
    }

    long int getQuantidadeNota100Disponiveis()
    {
        return quantidadeNota100Disponiveis;
    }

    long int getQuantidadeNota10Utilizadas()
    {
        return quantidadeNota10Utilizadas;
    }

    long int getQuantidadeNota20Utilizadas()
    {
        return quantidadeNota20Utilizadas;
    }

    long int getQuantidadeNota50Utilizadas()
    {
        return quantidadeNota50Utilizadas;
    }

    long int getQuantidadeNota100Utilizadas()
    {
        return quantidadeNota100Utilizadas;
    }

    long int getTotal()
    {
        return total;
    }

    long int getResto()
    {
        return resto;
    }
};

/*
 * Esta estrutura representa o resto e a quantidade
 * de notas distribuídas dado um determinado valor.
 */
struct restoAndQuantidade
{
    long int resto;
    long int quantidade;
};

/*
 * Esta estrutura representa um saque. 
 * Contém uma lista de opções de saque e 
 * o status do saque.
 */
struct Saque
{
    list<OpcaoSaque> opcoesSaque;
    bool aprovado;
};

/*
 * Esta classe representa un caixa eletrônico.
 */
class CaixaEletronico
{
private:
    // Atributos
    long int quantidadeNota10;
    long int quantidadeNota20;
    long int quantidadeNota50;
    long int quantidadeNota100;
    long int saldo; // long int - 32 bits
    // long long int saldo;    // long long int (C++11) - 64 bits

public:
    // Construtor
    CaixaEletronico(long int qtdeNota10, long int qtdeNota20,
                    long int qtdeNota50, long int qtdeNota100)
    {
        quantidadeNota10 = qtdeNota10;
        quantidadeNota20 = qtdeNota20;
        quantidadeNota50 = qtdeNota50;
        quantidadeNota100 = qtdeNota100;
    }

    // Destrutor
    ~CaixaEletronico()
    {
    }

    // Gets
    long int getSaldo()
    {
        return quantidadeNota10 * 10 + quantidadeNota20 * 20 +
               quantidadeNota50 * 50 + quantidadeNota100 * 100;
    }

    long int getQuantidadeNota10()
    {
        return quantidadeNota10;
    }

    long int getQuantidadeNota20()
    {
        return quantidadeNota20;
    }

    long int getQuantidadeNota50()
    {
        return quantidadeNota50;
    }

    long int getQuantidadeNota100()
    {
        return quantidadeNota100;
    }

    // Regras de negócio

    /**
     * Abastece o caixa eletônico.
     *
     * Registra o abastecimento de notas de 10, 20, 50 e 100 no caixa eletrônico.
     * 
     * @param nota Contém o valor que representa a nota (10, 2, 50, ou 100).
     * @param quantidade Contém o qubatidade de notas a serem abastecidadas.
     */
    void abastecer(int nota, long quantidade)
    {
        switch (nota)
        {
        case 10:
            quantidadeNota10 += quantidade;
            saldo += nota * quantidade;
            break;
        case 20:
            quantidadeNota20 += quantidade;
            saldo += nota * quantidade;
            break;
        case 50:
            quantidadeNota50 += quantidade;
            saldo += nota * quantidade;
            break;
        case 100:
            quantidadeNota100 += quantidade;
            saldo += nota * quantidade;
            break;
        }
    }

    /**
     * Aprova saque
     *
     * Aprova ou rejeita o saque de uma determinada quantia.
     * Informa quais notas devem ser liberadas para um saque aprovado.
     * 
     * @param valor Contém o valor que a ser aprovado para saque.
     * @return uma estrutura do tipo Saque.
     */
    Saque aprovar(long int valor)
    {
        Saque saque;
        list<OpcaoSaque> ops;

        /**
         * O saque deve ser rejeitado caso a quantia solicitada
         *  for maior que a quantia existente em caixa
         */
        if (getSaldo() < valor)
        {
            saque.aprovado = false;
        }
        else
        {
            saque.opcoesSaque = gerarOpcoesSaque(valor);

            // Rejeita o saque se não tiver nenhuma opção de saque.
            if (saque.opcoesSaque.empty())
            {
                saque.aprovado = false;
            }
            else
            {
                saque.aprovado = true;
            }
        }

        return saque;
    }

    /**
     * Gera uma opção de saque
     * 
     * @param per_n100 Contém o porcentagem para distribuição de notas de 100.
     * @param per_n50 Contém o porcentagem para distribuição de notas de 50.
     * @param per_n20 Contém o porcentagem para distribuição de notas de 20.
     * @param per_n10 Contém o porcentagem para distribuição de notas de 10.
     * @param valor Contém o valor para saque.
     * @return uma opção de saque.
     */
    OpcaoSaque gerarOpcaoSaque(long int per_n100,
                               long int per_n50, 
                               long int per_n20, 
                               long int per_n10, 
                               long int valor)
    {
        OpcaoSaque op(valor, quantidadeNota100, quantidadeNota50, 
                      quantidadeNota20, quantidadeNota10);

        // Faz a distribuição conforme a porcentagem das notas
        op = distribuir(per_n100, per_n50, per_n20, per_n10, op, false);

        /** Faz a dsitribuição das notas conforme o resto, 
         * para prencher o valor toal solicitado.
         **/ 
        op = distribuir(100, 100, 100, 100, op, true);

        return op;
    }

    /**
     * Distribui as notas para o valor de saque.
     * 
     * @param per_n100 Contém o porcentagem para distribuição de notas de 100.
     * @param per_n50 Contém o porcentagem para distribuição de notas de 50.
     * @param per_n20 Contém o porcentagem para distribuição de notas de 20.
     * @param per_n10 Contém o porcentagem para distribuição de notas de 10.
     * @param OpcaoSaque Contém a opcão de sauqe que está sendo gerada.
     * @param preencher Contém a indicação se o valor restante do saque deve ser distribuído.
     * @return uma opção de saque.
     */
    OpcaoSaque distribuir(long int per_n100, long int per_n50,
                          long int per_n20, long int per_n10, 
                          OpcaoSaque op, bool preencher)
    {
        long int qtd;
        restoAndQuantidade rq;

        // Distribui a nota de 100
        rq = distribuirNota(100, op.getQuantidadeNota100Disponiveis(), 
                            op.getQuantidadeNota100Utilizadas(), per_n100, 
                            op.getTotal(), op.getResto(), preencher);
        op.incrementarQuantidadeNota100Utilizadas(rq.quantidade);
        op.setResto(rq.resto);

        // Distribui a nota de 50
        rq = distribuirNota(50, op.getQuantidadeNota50isponiveis(),
                            op.getQuantidadeNota50Utilizadas(), per_n50, 
                            op.getTotal(), op.getResto(), preencher);
        op.incrementarQuantidadeNota50Utilizadas(rq.quantidade);
        op.setResto(rq.resto);

        // Distribui a nota de 20
        rq = distribuirNota(20, op.getQuantidadeNota20Disponiveis(),
                            op.getQuantidadeNota20Utilizadas(), per_n20, 
                            op.getTotal(), op.getResto(), preencher);
        op.incrementarQuantidadeNota120Utilizadas(rq.quantidade);
        op.setResto(rq.resto);

        // Distribui a nota de 10
        rq = distribuirNota(10, op.getQuantidadeNota10Disponiveis(), 
                            op.getQuantidadeNota10Utilizadas(), per_n10, 
                            op.getTotal(), op.getResto(), preencher);
        op.incrementarQuantidadeNota10Utilizadas(rq.quantidade);
        op.setResto(rq.resto);

        return op;
    }

    /**
     * Gera uma lista de opções de saque
     * 
     * @param valor Contém o valor para saque.
     * @return uma lista de opções de saque ou empty.
     */
    list<OpcaoSaque> gerarOpcoesSaque(long int valor)
    {
        list<OpcaoSaque> ops;

        // Gera a primeira opção de saque.
        OpcaoSaque op1 = gerarOpcaoSaque(100, 0, 0, 0, valor);
        if (op1.getResto() == 0)
        {
            ops.push_back(op1);
        }

        // Gera a segunda opção de saque.
        OpcaoSaque op2 = gerarOpcaoSaque(50, 20, 20, 10, valor);
        if (op2.getResto() == 0)
        {
            ops.push_back(op2);
        }

        // Gera a terceira opção de saque.
        OpcaoSaque op3 = gerarOpcaoSaque(20, 25, 45, 10, valor);
        if (op3.getResto() == 0)
        {
            ops.push_back(op3);
        }

        return ops;
    }

    /**
     * Distribui um tipo de nota para o valor de saque.
     * 
     * @param nota Contém o valor que representa a nota (10, 2, 50, ou 100).
     * @param quantidade_disponivel Contém a quantidade de notas disponíveis.
     * @param quantidade_utilizada Contém a quantidade de notas utilizadas.
     * @param porcentagem_nota Contém o porcentagem para distribuição das notas.
     * @param total Contém o valor total do saque para distribuição.
     * @param resto Contém o valor restante do saque para distribuição.
     * @param preencher Contém a indicação se o valor restante do saque deve ser distribuído.
     * @return uma estrutura que representa o resto e a quantidade de notas da distribuição.
     */
    restoAndQuantidade distribuirNota(int nota, long int quantidade_disponivel, 
                                      long int quantidade_utilizada, 
                                      long int porcentagem_nota, 
                                      long int total, long int resto, 
                                      bool preencher)
    {
        long int qtd, valor_nota;
        restoAndQuantidade rq;

        if (preencher)
        {
            valor_nota = (resto / 100.00) * porcentagem_nota;
        }
        else
        {
            valor_nota = (total / 100.00) * porcentagem_nota;
        }

        qtd = valor_nota / nota;
        if (qtd > quantidade_disponivel - quantidade_utilizada)
        {
            resto -= (quantidade_disponivel - quantidade_utilizada) * nota;
            qtd = quantidade_disponivel - quantidade_utilizada;
        }
        else
        {
            resto -= qtd * nota;
        }

        rq.resto = resto;
        rq.quantidade = qtd;

        return rq;
    }

    /**
     * Efetua o saque.
     * 
     * Conclui o saque conforme a opção de saque selecionada, após sua validação e aprovação.
     * 
     * @param op Contém o identificador da opção de saque selecionada.
     * @param opcoesSaque Contém a lista de opções de saque liberada.
     */
    void sacar(int op, list<OpcaoSaque> opcoesSaque)
    {
        int i = 0;

        for (OpcaoSaque opcaoSaque : opcoesSaque)
        {
            i++;
            if (op == i)
            {
                quantidadeNota100 -= opcaoSaque.getQuantidadeNota100Utilizadas();
                quantidadeNota50 -= opcaoSaque.getQuantidadeNota50Utilizadas();
                quantidadeNota20 -= opcaoSaque.getQuantidadeNota20Utilizadas();
                quantidadeNota10 -= opcaoSaque.getQuantidadeNota10Utilizadas();
            }
        }
    }
};

/**
 * Exemplo de menu para opção 1:
 *      Abastecer caixa eletrônico.
 */
void menuOpcao1(CaixaEletronico &c)
{
    char op;
    long int qtd;

    do
    {
        cout << endl << "Abastecer" << endl;
        cout << "*******************************" << endl;
        cout << " 1 - Abastecer notas de 10" << endl;
        cout << " 2 - Abastecer notas de 20" << endl;
        cout << " 3 - Abastecer notas de 50" << endl;
        cout << " 4 - Abastecer notas de 100" << endl << endl;
        cout << " 0 - Voltar ao nenu principal" << endl;
        cout << "*******************************" << endl << endl;
        cout << "Informe a opção desejada e pressione Enter: ";
        cin >> op;

        switch (op)
        {
        case '1':
            cout << "Informe a quantidade de notas de 10 e pressione Enter: ";
            cin >> qtd;
            c.abastecer(10, qtd);
            cout << "Operação concluída!" << endl;
            break;
        case '2':
            cout << "Informe a quantidade de notas de 20 e pressione Enter: ";
            cin >> qtd;
            c.abastecer(20, qtd);
            cout << "Operação concluída!" << endl;
            break;
        case '3':
            cout << "Informe a quantidade de notas de 50 e pressione Enter: ";
            cin >> qtd;
            c.abastecer(50, qtd);
            cout << "Operação concluída!" << endl;
            break;
        case '4':
            cout << "Informe a quantidade de notas de 100 e pressione Enter: ";
            cin >> qtd;
            c.abastecer(100, qtd);
            cout << "Operação concluída!" << endl;
            break;
        case '0':
            cout << endl;
            break;
        default:
            cout << "Opção inválida!" << endl << endl;
        }
    } while (op != '0');
}

/**
 * Exemplo de menu para opção 2:
 *      Sacar uma determinada qauntia do caixa eletrônico.
 */
void menuOpcao2(CaixaEletronico &c)
{
    char op;
    long int valor;
    Saque saque;
    int i;

    cout << endl << "*******************************" << endl;
    cout << "Sacar" << endl;
    cout << "*******************************" << endl << endl;
    cout << "Informe a quantia desejada e pressione Enter: ";
    cin >> valor;
    saque = c.aprovar(valor);
    if (saque.aprovado)
    {
        cout << "Saque aprovado!" << endl;
        do
        {
            cout << endl << "*******************************" << endl;
            cout << "Opções de saque:" << endl;
            cout << "*******************************" << endl;
            i = 0;
            for (OpcaoSaque opcaoSaque : saque.opcoesSaque)
            {
                i++;
                cout << " " << i << " - Opção de saque " << i << endl;
                cout << "   - " << opcaoSaque.getQuantidadeNota100Utilizadas()
                                << " notas de 100" << endl;
                cout << "   - " << opcaoSaque.getQuantidadeNota50Utilizadas() 
                                << " notas de 50" << endl;
                cout << "   - " << opcaoSaque.getQuantidadeNota20Utilizadas() 
                                << " notas de 20" << endl;
                cout << "   - " << opcaoSaque.getQuantidadeNota10Utilizadas() 
                                << " notas de 10" << endl << endl;
            }
            cout << " 0 - Cancelar" << endl;
            cout << "*******************************" << endl << endl;
            cout << "Informe a opção desejada e pressione Enter: ";
            cin >> op;

            switch (op)
            {
            case '1':
                c.sacar(op - '0', saque.opcoesSaque);
                cout << "Saque realizado com sucesso!" << endl;
                op = '0';
                break;
            case '2':
                c.sacar(op - '0', saque.opcoesSaque);
                cout << "Saque realizado com sucesso!" << endl;
                op = '0';
                break;
            case '3':
                c.sacar(op - '0', saque.opcoesSaque);
                cout << "Saque realizado com sucesso!" << endl;
                op = '0';
                break;
            case '0':
                cout << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
            }
        } while (op != '0');
    }
    else
    {
        cout << "Saque rejeitado!" << endl;
    }
    cout << endl;
}

/**
 * Exemplo de menu principal:
 *      Caixa eletrônico.
 */
void menuPrincipal(CaixaEletronico &c)
{
    char op;

    do
    {
        cout << "*******************************" << endl;
        cout << "Caixa Eletrônico" << endl;
        cout << "*******************************" << endl;
        cout << "Saldo: " << c.getSaldo() << endl;
        cout << "Notas de 10: " << c.getQuantidadeNota10() << endl;
        cout << "Notas de 20: " << c.getQuantidadeNota20() << endl;
        cout << "Notas de 50: " << c.getQuantidadeNota50() << endl;
        cout << "Notas de 100: " << c.getQuantidadeNota100() << endl << endl;
        cout << "*******************************" << endl;
        cout << " Menu" << endl;
        cout << "*******************************" << endl;
        cout << " 1 - Abastecer" << endl;
        cout << " 2 - Sacar" << endl << endl;
        cout << " 0 - Sair" << endl;
        cout << "*******************************" << endl << endl;
        cout << "Informe a opção desejada e pressione Enter: ";
        cin >> op;

        switch (op)
        {
        case '1':
            menuOpcao1(c);
            break;
        case '2':
            menuOpcao2(c);
            break;
        default:
            cout << "Opção inválida!" << endl;
        }
    } while (op != '0');
}

/*
 * Esta classe representa testes unitários.
 */
class UnitTest
{
public:
    /**
     * Teste unitário para o método getSaldo da classe CaixaEletronico
     */
    void testCaixaEletronicoGetSaldo()
    {
        CaixaEletronico c1(100, 100, 100, 100);
        auto actual = c1.getSaldo();
        auto expected = 18000;
        assert(expected == actual);
    }

    /**
     * Teste unitário para o método abastecer da classe CaixaEletronico
     */
    void testCaixaEletronicoAbastecer()
    {
        CaixaEletronico c1(100, 100, 100, 100);
        c1.abastecer(100, 10);
        c1.abastecer(50, 10);
        c1.abastecer(20, 10);
        c1.abastecer(10, 10);
        auto actual = c1.getSaldo();
        auto expected = 19800;
        assert(expected == actual);
    }

    /**
     * Teste unitário para o método aprovar da classe CaixaEletronico
     */
    void testCaixaEletronicoAprovar()
    {
        CaixaEletronico c1(100, 100, 100, 100);
        Saque s1 = c1.aprovar(900);
        Saque s2 = c1.aprovar(809);
        assert(s1.aprovado == true);
        assert(s2.aprovado == false);
        int i = 0;
        for (OpcaoSaque opcaoSaque : s1.opcoesSaque)
        {
            i++;
            switch (i)
            {
            case 1:
                assert(opcaoSaque.getQuantidadeNota100Utilizadas() == 9);
                assert(opcaoSaque.getQuantidadeNota50Utilizadas() == 0);
                assert(opcaoSaque.getQuantidadeNota20Utilizadas() == 0);
                assert(opcaoSaque.getQuantidadeNota10Utilizadas() == 0);
                break;
            case 2:
                assert(opcaoSaque.getQuantidadeNota100Utilizadas() == 4);
                assert(opcaoSaque.getQuantidadeNota50Utilizadas() == 4);
                assert(opcaoSaque.getQuantidadeNota20Utilizadas() == 10);
                assert(opcaoSaque.getQuantidadeNota10Utilizadas() == 10);
                break;
            case 3:
                assert(opcaoSaque.getQuantidadeNota100Utilizadas() == 2);
                assert(opcaoSaque.getQuantidadeNota50Utilizadas() == 4);
                assert(opcaoSaque.getQuantidadeNota20Utilizadas() == 20);
                assert(opcaoSaque.getQuantidadeNota10Utilizadas() == 10);
                break;
            }
        }
    }

    /**
     * Teste unitário para o método gerarOpcaoSaque da classe CaixaEletronico
     */
    void testCaixaEletronicoGerarOpcaoSaque()
    {
        CaixaEletronico c1(100, 100, 100, 100);
        OpcaoSaque op1 = c1.gerarOpcaoSaque(100, 0, 0, 0, 900);
        assert(op1.getQuantidadeNota100Utilizadas() == 9);
        assert(op1.getQuantidadeNota50Utilizadas() == 0);
        assert(op1.getQuantidadeNota20Utilizadas() == 0);
        assert(op1.getQuantidadeNota10Utilizadas() == 0);

        OpcaoSaque op2 = c1.gerarOpcaoSaque(50, 20, 20, 10, 900);
        assert(op2.getQuantidadeNota100Utilizadas() == 4);
        assert(op2.getQuantidadeNota50Utilizadas() == 4);
        assert(op2.getQuantidadeNota20Utilizadas() == 10);
        assert(op2.getQuantidadeNota10Utilizadas() == 10);

        OpcaoSaque op3 = c1.gerarOpcaoSaque(20, 25, 45, 10, 900);
        assert(op3.getQuantidadeNota100Utilizadas() == 2);
        assert(op3.getQuantidadeNota50Utilizadas() == 4);
        assert(op3.getQuantidadeNota20Utilizadas() == 20);
        assert(op3.getQuantidadeNota10Utilizadas() == 10);
    }

    /**
     * Teste unitário para o método distribuir da classe CaixaEletronico
     */
    void testCaixaEletronicoDistribuir()
    {
        CaixaEletronico c1(100, 100, 100, 100);
        OpcaoSaque op(900, 100, 100, 100, 100);
        OpcaoSaque op1 = c1.distribuir(100, 0, 0, 0, op, false);
        assert(op1.getQuantidadeNota100Utilizadas() == 9);
        assert(op1.getQuantidadeNota50Utilizadas() == 0);
        assert(op1.getQuantidadeNota20Utilizadas() == 0);
        assert(op1.getQuantidadeNota10Utilizadas() == 0);

        op1 = c1.distribuir(100, 100, 100, 100, op1, true);
        assert(op1.getQuantidadeNota100Utilizadas() == 9);
        assert(op1.getQuantidadeNota50Utilizadas() == 0);
        assert(op1.getQuantidadeNota20Utilizadas() == 0);
        assert(op1.getQuantidadeNota10Utilizadas() == 0);

        OpcaoSaque op2 = c1.distribuir(50, 20, 20, 10, op, false);

        assert(op2.getQuantidadeNota100Utilizadas() == 4);
        assert(op2.getQuantidadeNota50Utilizadas() == 3);
        assert(op2.getQuantidadeNota20Utilizadas() == 9);
        assert(op2.getQuantidadeNota10Utilizadas() == 9);

        op2 = c1.distribuir(100, 100, 100, 100, op2, true);
        assert(op2.getQuantidadeNota100Utilizadas() == 4);
        assert(op2.getQuantidadeNota50Utilizadas() == 4);
        assert(op2.getQuantidadeNota20Utilizadas() == 10);
        assert(op2.getQuantidadeNota10Utilizadas() == 10);

        OpcaoSaque op3 = c1.distribuir(20, 25, 45, 10, op, false);
        assert(op3.getQuantidadeNota100Utilizadas() == 1);
        assert(op3.getQuantidadeNota50Utilizadas() == 4);
        assert(op3.getQuantidadeNota20Utilizadas() == 20);
        assert(op3.getQuantidadeNota10Utilizadas() == 9);

        op3 = c1.distribuir(100, 100, 100, 100, op3, true);
        assert(op3.getQuantidadeNota100Utilizadas() == 2);
        assert(op3.getQuantidadeNota50Utilizadas() == 4);
        assert(op3.getQuantidadeNota20Utilizadas() == 20);
        assert(op3.getQuantidadeNota10Utilizadas() == 10);
    }

    /**
     * Teste unitário para o método gerarOpcoesSaque da classe CaixaEletronico
     */
    void testCaixaEletronicoGerarOpcoesSaque()
    {
        CaixaEletronico c1(100, 100, 100, 100);
        list<OpcaoSaque> opcoesSaque = c1.gerarOpcoesSaque(900);
        int i = 0;
        for (OpcaoSaque opcaoSaque : opcoesSaque)
        {
            i++;
            switch (i)
            {
            case 1:
                assert(opcaoSaque.getQuantidadeNota100Utilizadas() == 9);
                assert(opcaoSaque.getQuantidadeNota50Utilizadas() == 0);
                assert(opcaoSaque.getQuantidadeNota20Utilizadas() == 0);
                assert(opcaoSaque.getQuantidadeNota10Utilizadas() == 0);
                break;
            case 2:
                assert(opcaoSaque.getQuantidadeNota100Utilizadas() == 4);
                assert(opcaoSaque.getQuantidadeNota50Utilizadas() == 4);
                assert(opcaoSaque.getQuantidadeNota20Utilizadas() == 10);
                assert(opcaoSaque.getQuantidadeNota10Utilizadas() == 10);
                break;
            case 3:
                assert(opcaoSaque.getQuantidadeNota100Utilizadas() == 2);
                assert(opcaoSaque.getQuantidadeNota50Utilizadas() == 4);
                assert(opcaoSaque.getQuantidadeNota20Utilizadas() == 20);
                assert(opcaoSaque.getQuantidadeNota10Utilizadas() == 10);
                break;
            }
        }
    }

    /**
     * Teste unitário para o método distribuirNota da classe CaixaEletronico
     */
    void testCaixaEletronicoDistribuirNota()
    {
        CaixaEletronico c1(100, 100, 100, 100);
        restoAndQuantidade rq = c1.distribuirNota(100, 100, 0, 100, 900, 900, false);
        assert(rq.resto == 0);
        assert(rq.quantidade == 9);

        rq = c1.distribuirNota(100, 100, 0, 100, 900, 900, true);
        assert(rq.resto == 0);
        assert(rq.quantidade == 9);

        rq = c1.distribuirNota(50, 100, 50, 100, 900, 900, false);
        assert(rq.resto == 0);
        assert(rq.quantidade == 18);

        rq = c1.distribuirNota(100, 100, 100, 100, 900, 900, true);
        assert(rq.resto == 900);
        assert(rq.quantidade == 0);

        rq = c1.distribuirNota(20, 100, 0, 100, 900, 200, true);
        assert(rq.resto == 0);
        assert(rq.quantidade == 10);

        rq = c1.distribuirNota(10, 100, 0, 100, 900, 900, false);
        assert(rq.resto == 0);
        assert(rq.quantidade == 90);
    }

    /**
     * Teste unitário para o método gerarOpcoesSaque da classe CaixaEletronico
     */
    void testCaixaEletronicoSacar()
    {
        CaixaEletronico c1(100, 100, 100, 100);
        list<OpcaoSaque> opcoesSaque = c1.gerarOpcoesSaque(900);

        c1.sacar(1, opcoesSaque);
        assert(c1.getSaldo() == 17100);
        assert(c1.getQuantidadeNota100() == 91);
        assert(c1.getQuantidadeNota50() == 100);
        assert(c1.getQuantidadeNota20() == 100);
        assert(c1.getQuantidadeNota10() == 100);

        c1.sacar(2, opcoesSaque);
        assert(c1.getSaldo() == 16200);
        assert(c1.getQuantidadeNota100() == 87);
        assert(c1.getQuantidadeNota50() == 96);
        assert(c1.getQuantidadeNota20() == 90);
        assert(c1.getQuantidadeNota10() == 90);

        c1.sacar(3, opcoesSaque);
        assert(c1.getSaldo() == 15300);
        assert(c1.getQuantidadeNota100() == 85);
        assert(c1.getQuantidadeNota50() == 92);
        assert(c1.getQuantidadeNota20() == 70);
        assert(c1.getQuantidadeNota10() == 80);
    }
};

/**
 * Main
 */
int main()
{
    // Testes unitários.
    UnitTest unitTest;
    unitTest.testCaixaEletronicoGetSaldo();
    unitTest.testCaixaEletronicoAbastecer();
    unitTest.testCaixaEletronicoAprovar();
    unitTest.testCaixaEletronicoGerarOpcaoSaque();
    unitTest.testCaixaEletronicoDistribuir();
    unitTest.testCaixaEletronicoGerarOpcoesSaque();
    unitTest.testCaixaEletronicoDistribuirNota();
    unitTest.testCaixaEletronicoSacar();

    // Exemplo de menu para um caixa eletrônico.
    CaixaEletronico c1(100, 100, 100, 100);
    menuPrincipal(c1);

    return 0;
}
