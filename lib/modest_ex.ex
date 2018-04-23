defmodule ModestEx do
  @moduledoc """
  This module exposes features to do pipeable transformations on html strings with CSS selectors, e.g. find(), prepend(), append(), replace() etc.

  ## Credits:

  The package implements bindings to [Alexander Borisov's Modest](https://github.com/lexborisov/Modest).
  The binding is implemented as a C-Node based on the excellent example of [Lukas Rieder's cnodex](https://github.com/Overbryd/nodex) and [myhtmlex](https://github.com/Overbryd/myhtmlex).

  ## Example

    iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
    "<a>Hello</a>"

  """

  @type success() :: String.t() | [String.t()]
  @type error() :: {:error, String.t()}
  @type input() :: String.t() | [String.t()]

  def delimiter() do
    Application.get_env(:modest_ex, :delimiter, "|")
  end

  @moduledoc """
  Serialization scope.
  Possible values are:
  :html
    html will be serialized to complete document
    <html><head></head><body>...</body></html>

  :head
    html will be reduced only to the head fragment
    <head>...</head>

  :body
    html will be reduced only to the body fragment
    <body>...</body>

  :body_children
    html will be reduced to the children of the body

  """
  def scope() do
    Application.get_env(:modest_ex, :scope, :body_children) |> to_scope()
  end

  def to_scope(flag) when is_atom(flag) do
    case flag do
      :html -> flag
      :head -> flag
      :body -> flag
      :body_children -> flag
      _ -> :html
    end
    |> Atom.to_string()
  end

  def resolve(list) when is_list(list) do
    cond do
      Enum.count(list) == 1 -> List.first(list)
      true -> list
    end
  end

  @doc """
  Find nodes with a CSS selector.
  Returns the outer html of each node as a list of strings.

  ## Examples

    iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
    "<a>Hello</a>"

    iex> ModestEx.find("<p><span>Hello</span> <span>World</span></p>", "span")
    ["<span>Hello</span>", "<span>World</span>"]

  """
  @spec find(input(), String.t()) :: success() | error()
  def find(bin, selector) do
    ModestEx.Find.find(bin, selector)
  end

  @doc """
  Serialize any string with valid or broken html.
  Returns valid html string.

  ## Examples

    iex> ModestEx.serialize("<div>Hello<span>World")
    "<html><head></head><body><div>Hello<span>World</span></div></body></html>"

  """
  @spec serialize(input(), Atom.t()) :: success() | error()
  def serialize(bin, scope \\ :html) do
    ModestEx.Serialize.serialize(bin, scope)
  end

  @doc """
  Get all attributes with key.
  Returns list of strings.

  ## Examples

    iex> ModestEx.get_attribute("<a href=\\"https://elixir-lang.org\\">Hello</a>", "href")
    "https://elixir-lang.org"

  """
  @spec get_attribute(input(), String.t()) :: success() | error()
  def get_attribute(bin, key) do
    ModestEx.GetAttribute.get_attribute(bin, key)
  end

  @spec get_attribute(input(), String.t(), String.t()) :: success() | error()
  def get_attribute(bin, selector, key) do
    ModestEx.GetAttribute.get_attribute(bin, selector, key)
  end

  @doc """
  Set value for all attributes with key.
  Returns single html string or returns list of strings.

  ## Examples

    iex> ModestEx.set_attribute("<a>Hello</a>", "a", "href", "https://elixir-lang.org")
    "<a href=\\"https://elixir-lang.org\\">Hello</a>"

  """
  @spec set_attribute(input(), String.t(), String.t(), input()) :: success() | error()
  def set_attribute(bin, selector, key, value) do
    ModestEx.SetAttribute.set_attribute(bin, selector, key, value)
  end

  @doc """
  Get all text.
  Returns list of strings.

  ## Examples

    iex> ModestEx.get_text("<div>Hello World</div>")
    "Hello World"

  """
  @spec get_text(input()) :: success() | error()
  def get_text(bin) do
    ModestEx.GetText.get_text(bin)
  end

  @spec get_text(input(), String.t()) :: success() | error()
  def get_text(bin, selector) do
    ModestEx.GetText.get_text(bin, selector)
  end

  @doc """
  Set text for all nodes.
  Returns single html string or returns list of strings.

  ## Examples

    iex> ModestEx.set_text("<div><p>Hello</p></div>", "div p", "World")
    "<div><p>World</p></div>"

  """
  @spec set_text(input(), String.t(), input()) :: success() | error()
  def set_text(bin, selector, text) do
    ModestEx.SetText.set_text(bin, selector, text)
  end

  @doc """
  Remove nodes with a CSS selector.
  Returns updated html string

  ## Examples

    iex> ModestEx.remove("<div><p>Hello</p>World</div>", "div p")
    "<div>World</div>"

  """
  @spec remove(input(), String.t()) :: success() | error()
  def remove(bin, selector) do
    ModestEx.Remove.remove(bin, selector)
  end

  @doc """
  Append new html as a child at the end of selected node.
  Returns updated html string

  ## Examples

    iex> ModestEx.append("<div><p>Hello</p></div>", "div", "<p>World</p>")
    "<div><p>Hello</p><p>World</p></div>"

  """
  @spec append(input(), String.t(), String.t()) :: success() | error()
  def append(bin, selector, new_bin) do
    ModestEx.Append.append(bin, selector, new_bin)
  end

  @doc """
  Prepend new html as a child at the beginning of selected node.
  Returns updated html string

  ## Examples

    iex> ModestEx.prepend("<div><p>World</p></div>", "div", "<p>Hello</p>")
    "<div><p>Hello</p><p>World</p></div>"

  """
  @spec prepend(input(), String.t(), String.t()) :: success() | error()
  def prepend(bin, selector, new_bin) do
    ModestEx.Prepend.prepend(bin, selector, new_bin)
  end

  @doc """
  Insert new html before selected node.
  Returns updated html string

  ## Examples

    iex> ModestEx.insert_before("<div><p>World</p></div>", "div p", "<p>Hello</p>")
    "<div><p>Hello</p><p>World</p></div>"

  """
  @spec insert_before(input(), String.t(), String.t()) :: success() | error()
  def insert_before(bin, selector, new_bin) do
    ModestEx.InsertBefore.insert_before(bin, selector, new_bin)
  end

  @doc """
  Insert new html after selected node.
  Returns updated html string

  ## Examples

    iex> ModestEx.insert_after("<div><p>Hello</p></div>", "div p", "<p>World</p>")
    "<div><p>Hello</p><p>World</p></div>"

  """
  @spec insert_after(input(), String.t(), String.t()) :: success() | error()
  def insert_after(bin, selector, new_bin) do
    ModestEx.InsertAfter.insert_after(bin, selector, new_bin)
  end

  @doc """
  Replace selected node with new html
  Returns updated html string

  ## Examples

    iex> ModestEx.replace("<div><p>Hello</p></div>", "div p", "<p>World</p>")
    "<div><p>World</p></div>"

  """
  @spec replace(input(), String.t(), String.t()) :: success() | error()
  def replace(bin, selector, new_bin) do
    ModestEx.Replace.replace(bin, selector, new_bin)
  end

  @doc """
  Slice selected set into subset.
  Returns single html string or returns list of strings.

  ## Examples

    iex> ModestEx.slice("<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>", "body > *", 0, -1)
    ["<h1>Lorem ipsum</h1>", "<p>dolor sit amet</p>", "<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>", "<p>Sed ut perspiciatis</p>", "<p>unde omnis iste natus</p>"]

  """
  @spec slice(input(), String.t(), Integer.t(), Integer.t()) :: success() | error()
  def slice(bin, selector, start_index, end_index) do
    ModestEx.Slice.slice(bin, selector, start_index, end_index)
  end

  @doc """
  Get position of selected nodes in in relation to its parent.
  Returns list of positions.

  ## Examples

    iex> ModestEx.position("<p>Hello</p><div></div><p>World</p>", "p")
    [1, 3]

  """
  @spec position(input(), String.t()) :: success() | error()
  def position(bin, selector) do
    ModestEx.Position.position(bin, selector)
  end

  @doc """
  Wrap an HTML structure around each element in the set of matched elements.
  Returns updated html string.

  ## Examples

    iex> ModestEx.wrap("<p>Hello</p><p>World</p>", "p", "<div></div>")
    "<div><p>Hello</p><p>World</p></div>"

  """
  @spec wrap(input(), String.t(), String.t()) :: success() | error()
  def wrap(bin, selector, new_bin) do
    ModestEx.Wrap.wrap(bin, selector, new_bin)
  end

  @doc """
  Pretty print html.

  ## Examples
    iex> ModestEx.pretty_print("<p>Hello World</p>")
    "<p>\\n\\tHello World\\n</p>\\n"

  """
  @spec pretty_print(input()) :: success() | error()
  def pretty_print(bin) do
    ModestEx.PrettyPrint.pretty_print(bin)
  end
end
