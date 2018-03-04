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

  test "more complex set_attribute/4" do
    result = "<div><div><a>Hello</a></div><div><a>World</a></div></div>"
    |> ModestEx.set_attribute("body > div", "class", "col-md-12")
    |> ModestEx.set_attribute("div.col-md-12 div", "class", "col-md-6")
    |> ModestEx.set_attribute("div.col-md-6:first-of-type a", "href", "https://elixir-lang.org")
    |> ModestEx.set_attribute("div.col-md-6:last-of-type a", "href", "https://google.de")

    assert result == "<html><head></head><body><div class=\"col-md-12\"><div class=\"col-md-6\"><a href=\"https://elixir-lang.org\">Hello</a></div><div class=\"col-md-6\"><a href=\"https://google.de\">World</a></div></div></body></html>"
  end

  test "find/2 |> set_attribute/3" do
    result = "<p><a>Hello</a><a>World</a></p>"
    |> ModestEx.find("a")
    |> ModestEx.set_attribute("href", "https://elixir-lang.org")
    assert result == ["<html><head></head><body><a href=\"https://elixir-lang.org\">Hello</a></body></html>", "<html><head></head><body><a href=\"https://elixir-lang.org\">World</a></body></html>"]
  end

  test "find/2 |> set_attribute/3 with list of values" do
    result = "<p><a>Hello</a><a>World</a></p>"
    |> ModestEx.find("a")
    |> ModestEx.set_attribute("href", ["https://elixir-lang.org", "https://google.de"])
    assert result == ["<html><head></head><body><a href=\"https://elixir-lang.org\">Hello</a></body></html>", "<html><head></head><body><a href=\"https://google.de\">World</a></body></html>"]
  end

  test "find/2 |> set_attribute/4" do
    result = "<p><span><a>Hello</a></span><span><a>World</a></span></p>"
    |> ModestEx.find("span")
    |> ModestEx.set_attribute("a", "href", "https://elixir-lang.org")
    assert result == ["<html><head></head><body><span><a href=\"https://elixir-lang.org\">Hello</a></span></body></html>", "<html><head></head><body><span><a href=\"https://elixir-lang.org\">World</a></span></body></html>"]
  end

  test "find/2 |> set_attribute/4 with list of values" do
    result = "<p><span><a>Hello</a></span><span><a>World</a></span></p>"
    |> ModestEx.find("span")
    |> ModestEx.set_attribute("a", "href", ["https://elixir-lang.org", "https://google.de"])
    assert result == ["<html><head></head><body><span><a href=\"https://elixir-lang.org\">Hello</a></span></body></html>", "<html><head></head><body><span><a href=\"https://google.de\">World</a></span></body></html>"]
  end

  test "find/2 |> get_text/1" do
    result = "<p><span><a>Hello</a></span><span><a>World</a></span></p>"
    |> ModestEx.find("span")
    |> ModestEx.get_text()
    assert result == ["Hello", "World"]
  end

  test "find/2 |> get_text/2" do
    result = "<p><div><p><a>Hello</a></p></div><div><p><a>World</a></p></div></p>"
    |> ModestEx.find("div")
    |> ModestEx.get_text("p a")
    assert result == ["Hello", "World"]
  end

  test "find/2 |> set_text/2" do
    result = "<p><span>Hello</span><span>World</span></p>"
    |> ModestEx.find("span")
    |> ModestEx.set_text("Hello")
    assert result == ["<html><head></head><body><span>Hello</span></body></html>", "<html><head></head><body><span>Hello</span></body></html>"]
  end

  test "find/2 |> set_text/3" do
    result = "<p><span><a>Hello</a></span><span><a>World</a></span></p>"
    |> ModestEx.find("span")
    |> ModestEx.set_text("a", ["Hello", "World"])
    assert result == ["<html><head></head><body><span><a>Hello</a></span></body></html>", "<html><head></head><body><span><a>World</a></span></body></html>"]
  end

  test "get_text/1" do
    result = "<p><span><a>Hello</a></span><span><a>World</a></span></p>"
    |> ModestEx.get_text()
    assert result == ["Hello", "World"]
  end

  test "get_text/2" do
    result = "<p><span><a>Hello</a></span><span><a>World</a></span></p>"
    |> ModestEx.get_text("span a")
    assert result == ["Hello", "World"]
  end

  test "set_text/3" do
    result = "<p><span><a>Hello</a></span><span><a>Hello</a></span></p>"
    |> ModestEx.set_text("a", "World")
    assert result == "<html><head></head><body><p><span><a>World</a></span><span><a>World</a></span></p></body></html>"
  end

  # test "set_text/3 with list" do
  #   result = "<p><span><a>Hello</a></span><span><a>World</a></span></p>"
  #   |> ModestEx.set_text("a", ["Hello", "World"])
  #   assert result == []
  # end

  test "find/2 |> remove/2" do
    result = "<p><span><a>Hello</a></span><span>World</span></p>"
    |> ModestEx.find("span")
    |> ModestEx.remove("a")
    assert result == ["<html><head></head><body><span></span></body></html>", "<html><head></head><body><span>World</span></body></html>"]
  end

end
