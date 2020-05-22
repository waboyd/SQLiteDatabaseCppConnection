.PHONY: clean All

All:
	@echo "----------Building project:[ SQLiteConnection - Debug ]----------"
	@cd "SQLiteConnection" && "$(MAKE)" -f  "SQLiteConnection.mk"
clean:
	@echo "----------Cleaning project:[ SQLiteConnection - Debug ]----------"
	@cd "SQLiteConnection" && "$(MAKE)" -f  "SQLiteConnection.mk" clean
