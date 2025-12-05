defmodule Demo do
  @moduledoc """
  Demo app to verify modest_ex installation and example code from README.
  """

  @doc """
  Run the example from README - build up a complete DOM using pipeable transformations.
  """
  def run do
    IO.puts("=== ModestEx Demo ===\n")
    IO.puts("Building DOM with pipeable transformations...\n")

    # Build up a complete DOM (example from README)
    result =
      ""
      |> ModestEx.serialize()
      |> ModestEx.append("body", "<div>")
      |> ModestEx.set_attribute("div", "class", "col-md-12")
      |> ModestEx.append("div", "<div>")
      |> ModestEx.set_attribute("div.col-md-12 div", "class", "col-md-6")
      |> ModestEx.append("div.col-md-12 div", "<a></a>")
      |> ModestEx.set_text("a", "Hello")

    IO.puts("Step 1 - Initial structure:")
    IO.puts(result)
    IO.puts("")

    copy =
      ModestEx.find(result, "div.col-md-12 div")
      |> ModestEx.set_text("a", "World")

    IO.puts("Step 2 - Copy with modified text:")
    IO.puts(copy)
    IO.puts("")

    result =
      ModestEx.insert_after(result, "div.col-md-12 div", copy)
      |> ModestEx.set_attribute("div.col-md-6:first-of-type a", "href", "https://elixir-lang.org")
      |> ModestEx.set_attribute("div.col-md-6:last-of-type a", "href", "https://google.de")

    IO.puts("Step 3 - Final result:")
    IO.puts(result)
    IO.puts("")

    expected =
      "<div class=\"col-md-12\"><div class=\"col-md-6\"><a href=\"https://elixir-lang.org\">Hello</a></div><div class=\"col-md-6\"><a href=\"https://google.de\">World</a></div></div>"

    if result == expected do
      IO.puts("SUCCESS: Result matches expected output!")
    else
      IO.puts("FAILURE: Result does not match expected output")
      IO.puts("Expected: #{expected}")
    end

    IO.puts("\n=== Demo Complete ===")
  end

  @doc """
  Run additional feature demos.
  """
  def run_all do
    run()

    IO.puts("\n=== Additional Feature Demos ===\n")

    # find/2
    IO.puts("find/2:")
    result = ModestEx.find("<p><a>Hello</a> World</p>", "p a")
    IO.puts("  ModestEx.find(\"<p><a>Hello</a> World</p>\", \"p a\")")
    IO.puts("  => #{inspect(result)}\n")

    # serialize/2
    IO.puts("serialize/2:")
    result = ModestEx.serialize("<div>Hello<span>World", :body_children)
    IO.puts("  ModestEx.serialize(\"<div>Hello<span>World\", :body_children)")
    IO.puts("  => #{inspect(result)}\n")

    # get_attribute/3
    IO.puts("get_attribute/3:")
    result = ModestEx.get_attribute("<p><a href=\"test\">Hello</a></p>", "a", "href")
    IO.puts("  ModestEx.get_attribute(\"<p><a href=\\\"test\\\">Hello</a></p>\", \"a\", \"href\")")
    IO.puts("  => #{inspect(result)}\n")

    # get_text/2
    IO.puts("get_text/2:")
    result = ModestEx.get_text("<p>Hello <span>World</span></p>", "span")
    IO.puts("  ModestEx.get_text(\"<p>Hello <span>World</span></p>\", \"span\")")
    IO.puts("  => #{inspect(result)}\n")

    # remove/2
    IO.puts("remove/2:")
    result = ModestEx.remove("<p><span>Hello</span> World</p>", "span")
    IO.puts("  ModestEx.remove(\"<p><span>Hello</span> World</p>\", \"span\")")
    IO.puts("  => #{inspect(result)}\n")

    # replace/3
    IO.puts("replace/3:")
    result = ModestEx.replace("<p><span>Hello</span></p>", "span", "<strong>World</strong>")
    IO.puts("  ModestEx.replace(\"<p><span>Hello</span></p>\", \"span\", \"<strong>World</strong>\")")
    IO.puts("  => #{inspect(result)}\n")

    IO.puts("=== All Demos Complete ===")
  end
end
