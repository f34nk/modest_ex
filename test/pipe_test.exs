defmodule PipeTest do
  use ExUnit.Case
  doctest ModestEx

  test "find/2 |> get_attribute/2" do
    result = "<p><a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://google.de\">World</a></p>"
    |> ModestEx.find("a")
    |> ModestEx.get_attribute("href")
    assert result == ["https://elixir-lang.org", "https://google.de"]
  end

  test "find/2 |> get_attribute/3" do
    result = "<p><span><a href=\"https://elixir-lang.org\">Hello</a></span><span><a href=\"https://google.de\">World</a></span></p>"
    |> ModestEx.find("span")
    |> ModestEx.get_attribute("a", "href")
    assert result == ["https://elixir-lang.org", "https://google.de"]
  end

  test "find/2 |> set_attribute/2" do
    result = "<p><a>Hello</a><a>World</a></p>"
    |> ModestEx.find("a")
    |> ModestEx.set_attribute("href", "https://elixir-lang.org")
    assert result == ["<html><head></head><body><a href=\"https://elixir-lang.org\">Hello</a></body></html>", "<html><head></head><body><a href=\"https://elixir-lang.org\">World</a></body></html>"]
  end

  test "find/2 |> set_attribute/3" do
    result = "<p><span><a href=\"https://elixir-lang.org\">Hello</a></span><span><a href=\"https://google.de\">World</a></span></p>"
    |> ModestEx.find("span")
    |> ModestEx.set_attribute("a", "href", "https://elixir-lang.org")
    assert result == ["<html><head></head><body><span><a href=\"https://elixir-lang.org\">Hello</a></span></body></html>", "<html><head></head><body><span><a href=\"https://elixir-lang.org\">World</a></span></body></html>"]
  end
end
