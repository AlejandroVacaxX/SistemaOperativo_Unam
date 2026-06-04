# Critical Rules for the AI

The following rules are mandatory and must be strictly followed by the AI during all code generation and interaction for this project.

## Code Commenting and Formatting Rules

1. **Language of Comments:**
   * All code comments inside source files (`.c`, `.h`, `.py`) MUST be written in Spanish.
   * The tone must be natural language (casual/conversational), NOT formal academic language.

2. **Orthography and Character Restrictions in Comments:**
   * The use of **accent marks** (á, é, í, ó, ú, ñ, etc.) is STRICTLY PROHIBITED in all code comments.
   * The use of **capital letters** (UPPERCASE) is STRICTLY PROHIBITED in all code comments. Every comment must be written entirely in lowercase.

3. **No Step-by-Step Lists in Comments:**
   * It is strictly prohibited to write sequential or step-by-step lists inside code comments (e.g., do NOT write `// 1. creamos la pila`, `// 2. usamos la pila`). Comments should describe the intent or mechanism fluidly without numbering steps.

4. **Visual Elements Restriction:**
   * The use of **emojis** is completely prohibited in code comments, commit suggestions, and markdown documentation. Keep explanations strictly text-based.

## Example of BAD vs GOOD Code Comments

### ❌ Incorrect (Violates uppercase, accents, formal tone, or step lists)
```c
// 1. Inicialización del Bloque de Memoria Principal.
// 2. Retornar el apuntador al inicio.
MemoryBlock* init_memory() {
    // Código aquí...
}
```

###  Correct (Lowercase, no accents, natural Spanish, no step numbers)
```c
// inicializamos el bloque de memoria vacio para empezar a trabajar desde cero
MemoryBlock* init_memory() {
    // codigo aqui...
}
```