.PHONY: clean All

All:
	@echo "----------Building project:[ SQLiteConnectionLibCompiler - Debug ]----------"
	@cd "SQLiteConnection" && "$(MAKE)" -f  "SQLiteConnectionLibCompiler.mk"
clean:
	@echo "----------Cleaning project:[ SQLiteConnectionLibCompiler - Debug ]----------"
	@cd "SQLiteConnection" && "$(MAKE)" -f  "SQLiteConnectionLibCompiler.mk" clean
