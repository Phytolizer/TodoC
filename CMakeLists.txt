cmake_minimum_required(VERSION 3.12...3.23)

project(
	Todo
	LANGUAGES C
	VERSION 0.1.0
	DESCRIPTION "Todo app for Terminal"
	HOMEPAGE_URL "https://github.com/Phytolizer/Todo"
)

add_executable(Todo main.c ansi_esc.c)
