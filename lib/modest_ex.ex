defmodule ModestEx do
  @moduledoc """
  This module exposes features to do pipeable transformations on html strings with CSS selectors, e.g. find(), prepend(), append(), replace() etc.

  ## Credits:

  The package implements bindings to [Alexander Borisov's Modest](https://github.com/lexborisov/Modest). 
  The binding is implemented as a C-Node based on the excellent example of [Lukas Rieder's cnodex](https://github.com/Overbryd/nodex) and [myhtmlex](https://github.com/Overbryd/myhtmlex).

  ## Example

    iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
    ["<a>Hello</a>"]

  """

  @type success() :: String.t | [String.t]
  @type error() :: {:error, String.t}
  @type input() :: String.t | [String.t]

  def delimiter() do
    Application.get_env(:modest_ex, :delimiter, "|")
  end

  #
  # TODO: Find better solution for String.split
  # String.split/2 is too slow with large strings
  # https://github.com/elixir-lang/elixir/issues/6148
  # 
  def split(bin) when is_bitstring(bin) do
    String.split(bin, ModestEx.delimiter())
  end

  @doc """
  Find nodes with a CSS selector.
  Returns the outer html of each node as a list of strings.

  ## Examples

    iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
    ["<a>Hello</a>"]

    iex> ModestEx.find("<p><span>Hello</span> <span>World</span></p>", "span")
    ["<span>Hello</span>", "<span>World</span>"]

  """
  @spec find(input(), String.t) :: success() | error()
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
  @spec serialize(input()) :: success() | error()
  def serialize(bin) do
    ModestEx.Serialize.serialize(bin)
  end

  @doc """
  Get all attributes with key.
  Returns list of strings.

  ## Examples

    iex> ModestEx.get_attribute("<a href=\\"https://elixir-lang.org\\">Hello</a>", "href")
    ["https://elixir-lang.org"]

  """
  @spec get_attribute(input(), String.t) :: success() | error()
  def get_attribute(bin, key) do
    ModestEx.GetAttribute.get_attribute(bin, key)
  end

  @spec get_attribute(input(), String.t, String.t) :: success() | error()
  def get_attribute(bin, selector, key) do
    ModestEx.GetAttribute.get_attribute(bin, selector, key)
  end

  @doc """
  Set value for all attributes with key.
  Returns single html string or returns list of strings.

  ## Examples

    iex> ModestEx.set_attribute("<a>Hello</a>", "href", "https://elixir-lang.org")
    "<html><head></head><body><a href=\\"https://elixir-lang.org\\">Hello</a></body></html>"

  """
  @spec set_attribute(input(), String.t, input()) :: success() | error()
  def set_attribute(bin, key, value) do
    ModestEx.SetAttribute.set_attribute(bin, key, value)
  end

  @spec set_attribute(input(), String.t, String.t, input()) :: success() | error()
  def set_attribute(bin, selector, key, value) do
    ModestEx.SetAttribute.set_attribute(bin, selector, key, value)
  end

end
