#include "semantic.h"

#include <stdio.h>

void Scan(char* rawSourceCode){
	BuildTree(rawSourceCode);
}

void BuildTree(char* rawSourceCode){
	Clock clock;
	StartClock(&clock);

	DEBUG_PRINT("\n\n------Starting Program------\n");

	// Build Lexer
	Lexer lexer;
	InitLexer(&lexer, rawSourceCode);

	// Pre-allocate memory
	// The heap is 3,000% slower than just using stack
	// memory. So we are pre-allocating the memory
	// using the stack
	int totalNodes = CountTotalASTTokens(&lexer);
	ResetLexer(&lexer);
	int totalScopes = CountTotalScopes(&lexer);
	ResetLexer(&lexer);

	// Pre-allocate the different variable types
	ASTNode nodes[totalNodes];
	InitNodes(nodes, totalNodes);

	// Pre-allocate the different scopes
	int scopes[totalScopes + 1];
	for (int i = 0; i < totalScopes + 1; i++){
		scopes[i] = i + 1;
	}

	// Build the scope
	Scope scope;
	InitScope(&scope);
	scope.nodeLength = totalNodes;
	scope.nodes = nodes;
	scope.scopeLength = totalScopes;
	scope.scopes = scopes;

	// Let's build the tree
	ParseStmtList(&scope, &lexer, scope.scopes[scope.scopeSpot++], false);
	scope.nodeSpot = 0;
	EnsureSemantics(&scope, 1);

	ExpandScope(&scope, 0);


	// Cleanup
	DestroyLexer(&lexer);
	DestroyNodes(nodes, totalNodes);
	DestroyScope(&scope);

	EndClock(&clock);
	SetClockDifference(&clock);
	DEBUG_PRINT("\n\n------Program Completed------\n");
	DEBUG_PRINT("\n\n------Program Stats------\n");
	printf("Time: %llu nanoseconds\n", GetClockNanosecond(&clock));
}

void EnsureSemantics(Scope* scope, int scopeId){
	ASTNode* node = GetNextNode(scope);

	if (node == NULL) return; // Done

	while (node != NULL){

		if (node->scopeId == scopeId){
			int type = (int) node->type;
			switch (type){
				case VAR: {
					PredictVarType(node);
					break;
				}
				case FOR: {
					PredictVarType(GET_FOR_VAR(node));
					if (GetBinaryType(GET_FOR_CONDITION(node)) != BOOLEAN) {
						SEMANTIC_ERROR("Invalid For loop condition");
					}
					EnsureSemantics(scope, GET_FOR_BODY(node));
					break;
				}
				case WHILE: {

				}
			}
		}

		node = GetNextNode(scope);
	}
}

void PredictVarType(ASTNode* node){
	DEBUG_PRINT3("Predicting Variable Type", GET_VAR(node).name, TokenToString(GET_VAR(node).dataType));

	if (node->type != VAR) return; // already assigned

	ASTNode* value = GET_VAR_VALUE(node);
	if (IsNumber(value->type) || IsString(value->type)){
		GET_VAR(node).dataType = value->type;
		DEBUG_PRINT2("Variable Type Set", TokenToString(GET_VAR(node).dataType));
	}
	else if (value->type == BINARY){
		GET_VAR(node).dataType = GetBinaryType(value);
		DEBUG_PRINT2("Variable Type Set", TokenToString(GET_VAR(node).dataType));
	}
}
