#include <iostream>
#include <vector>

using namespace std;

// Função auxiliar para imprimir o vetor (útil para testes)
void imprimirVetor(const vector<int>& arr) {
    cout << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ==========================================
// 1. BUBBLE SORT
// ==========================================
void bubble_sort(vector<int>& arr, int& comparacoes, int& trocas) {
    int n = arr.size();              // Armazena o tamanho do array na variável n
    comparacoes = 0;                 // Inicializa o contador de comparações em 0
    trocas = 0;                      // Inicializa o contador de trocas em 0
    
    for (int i = 0; i < n; i++) {    // Loop externo: controla o número de passadas pelo array
        bool trocou = false;         // Flag para verificar se houve troca nesta passada (otimização)
        
        for (int j = 0; j < n - i - 1; j++) { // Loop interno: compara elementos adjacentes
            comparacoes++;           // Incrementa 1 a cada comparação realizada
            
            if (arr[j] > arr[j + 1]) { // Verifica se o elemento atual é maior que o próximo
                int temp = arr[j];   // Variável temporária para realizar a troca
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocas++;            // Incrementa 1 a cada troca efetivada
                trocou = true;       // Atualiza a flag indicando que houve troca
            }
        }
        if (!trocou) break;          // Se nenhuma troca ocorreu, o array já está ordenado
    }
}

// ==========================================
// 2. SELECTION SORT
// ==========================================
void selection_sort(vector<int>& arr, int& comparacoes, int& trocas) {
    int n = arr.size();              // Armazena o comprimento total do array
    comparacoes = 0;                 // Inicializa o contador de comparações
    trocas = 0;                      // Inicializa o contador de trocas
    
    for (int i = 0; i < n; i++) {    // Loop externo: define o início da parte não ordenada
        int min_idx = i;             // Assume inicialmente que o primeiro elemento é o menor
        
        for (int j = i + 1; j < n; j++) { // Loop interno: percorre o restante para achar o menor
            comparacoes++;           // Incrementa o contador de comparações
            
            if (arr[j] < arr[min_idx]) { // Compara se o elemento atual é menor que o menor registrado
                min_idx = j;         // Atualiza o índice do menor elemento encontrado
            }
        }
        if (min_idx != i) {          // Se o índice do menor elemento mudou
            int temp = arr[i];       // Troca o menor elemento com a posição `i`
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            trocas++;                // Incrementa o contador de trocas
        }
    }
}

// ==========================================
// 3. INSERTION SORT
// ==========================================
void insertion_sort(vector<int>& arr, int& comparacoes, int& trocas) {
    int n = arr.size();              // Armazena o tamanho do array
    comparacoes = 0;                 // Inicializa o contador de comparações
    trocas = 0;                      // Inicializa o contador de deslocamentos/trocas
    
    for (int i = 1; i < n; i++) {    // Loop externo: começa do segundo elemento (índice 1)
        int chave = arr[i];          // Armazena o elemento atual (a "chave")
        int j = i - 1;               // Índice do elemento anterior à chave
        
        while (j >= 0) {             // Continua enquanto não chegar ao início do array
            comparacoes++;           // Incrementa a comparação realizada no while
            if (arr[j] > chave) {    // Se o elemento anterior for maior que a chave
                arr[j + 1] = arr[j]; // Desloca o elemento para a frente
                trocas++;            // Conta a movimentação
                j--;                 // Decrementa j para verificar o próximo à esquerda
            } else {
                break;               // Interrompe o while se não for maior
            }
        }
        arr[j + 1] = chave;          // Insere a chave na sua posição correta
    }
}

// ==========================================
// 4. MERGE SORT
// ==========================================
void merge(vector<int>& arr, int esquerda, int meio, int direita, int& comparacoes, int& trocas) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[esquerda + i];
    for (int j = 0; j < n2; j++) R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esquerda;

    while (i < n1 && j < n2) {
        comparacoes++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        trocas++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        trocas++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        trocas++;
    }
}

void merge_sort_rec(vector<int>& arr, int esquerda, int direita, int& comparacoes, int& trocas) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        merge_sort_rec(arr, esquerda, meio, comparacoes, trocas);
        merge_sort_rec(arr, meio + 1, direita, comparacoes, trocas);
        merge(arr, esquerda, meio, direita, comparacoes, trocas);
    }
}

void merge_sort(vector<int>& arr, int& comparacoes, int& trocas) {
    comparacoes = 0;
    trocas = 0;
    if (!arr.empty()) {
        merge_sort_rec(arr, 0, arr.size() - 1, comparacoes, trocas);
    }
}

// ==========================================
// 5. QUICK SORT
// ==========================================
int particionar(vector<int>& arr, int baixo, int alto, int& comparacoes, int& trocas) {
    int pivote = arr[alto];          // Escolhe o último elemento como pivô
    int i = (baixo - 1);
    
    for (int j = baixo; j <= alto - 1; j++) {
        comparacoes++;
        if (arr[j] <= pivote) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            trocas++;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[alto];
    arr[alto] = temp;
    trocas++;
    return (i + 1);
}

void quick_sort_rec(vector<int>& arr, int baixo, int alto, int& comparacoes, int& trocas) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto, comparacoes, trocas);
        quick_sort_rec(arr, baixo, pi - 1, comparacoes, trocas);
        quick_sort_rec(arr, pi + 1, alto, comparacoes, trocas);
    }
}

void quick_sort(vector<int>& arr, int& comparacoes, int& trocas) {
    comparacoes = 0;
    trocas = 0;
    if (!arr.empty()) {
        quick_sort_rec(arr, 0, arr.size() - 1, comparacoes, trocas);
    }
}

// ==========================================
// FUNÇÃO PRINCIPAL (MAIN)
// ==========================================
int main() {
    vector<int> entradaOriginal = {4, 2, 1, 3};
    int comp = 0, troc = 0;

    cout << "Array Original: ";
    imprimirVetor(entradaOriginal);
    cout << "----------------------------------------" << endl;

    // Teste Bubble Sort
    vector<int> arr1 = entradaOriginal;
    bubble_sort(arr1, comp, troc);
    cout << "Bubble Sort    -> Res: "; imprimirVetor(arr1);
    cout << "Comparações: " << comp << " | Trocas: " << troc << "\n\n";

    // Teste Selection Sort
    vector<int> arr2 = entradaOriginal;
    selection_sort(arr2, comp, troc);
    cout << "Selection Sort -> Res: "; imprimirVetor(arr2);
    cout << "Comparações: " << comp << " | Trocas: " << troc << "\n\n";

    // Teste Insertion Sort
    vector<int> arr3 = entradaOriginal;
    insertion_sort(arr3, comp, troc);
    cout << "Insertion Sort -> Res: "; imprimirVetor(arr3);
    cout << "Comparações: " << comp << " | Trocas: " << troc << "\n\n";

    // Teste Merge Sort
    vector<int> arr4 = entradaOriginal;
    merge_sort(arr4, comp, troc);
    cout << "Merge Sort     -> Res: "; imprimirVetor(arr4);
    cout << "Comparações: " << comp << " | Trocas: " << troc << "\n\n";

    // Teste Quick Sort
    vector<int> arr5 = entradaOriginal;
    quick_sort(arr5, comp, troc);
    cout << "Quick Sort     -> Res: "; imprimirVetor(arr5);
    cout << "Comparações: " << comp << " | Trocas: " << troc << "\n\n";

    return 0;
}