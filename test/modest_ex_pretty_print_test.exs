defmodule ModestExPrettyPrintTest do
  use ExUnit.Case
  doctest ModestEx

  test "pretty print" do
    result = ModestEx.pretty_print("<p>Hello World</p>")
    assert result == "<p>\n\tHello World\n</p>\n"

    # assert result == "\e[31m<\e[0m\e[31mp\e[0m\e[31m>\e[0m\e[0mHello World\e[0m\e[31m</\e[0m\e[31mp\e[0m\e[31m>\e[0m\n"
  end
end
