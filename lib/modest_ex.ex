defmodule ModestEx do
  @moduledoc """
  This module exposes features to find html nodes with CSS selectors and common methods to manipulate the DOM tree.

  ## Credits:

  The package implements bindings to [Alexander Borisov's Modest](https://github.com/lexborisov/Modest). 
  The binding is implemented as a C-Node based on the excellent example of [Lukas Rieser's cnodex](https://github.com/Overbryd/nodex) and [myhtmlex](https://github.com/Overbryd/myhtmlex).

  ## Example

    iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a", "|")
    {:ok, "<a>Hello</a>"}

  """

  @type success() :: {:ok, String.t}
  @type error() :: {:error, String.t}

  @doc """
  Find html nodes with a CSS selector.
  Returns the selected node as a html string.

  ## Examples

    iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a", "|")
    {:ok, "<a>Hello</a>"}

    iex> ModestEx.find("<p><span>Hello</span> <span>World</span></p>", "span")
    {:ok, "<span>Hello</span>|<span>World</span>"}

    iex> ModestEx.find("<p><span>Hello</span> <span>World</span></p>", "span", "( ͡ᵔ ͜ʖ ͡ᵔ )")
    {:ok, "<span>Hello</span>( ͡ᵔ ͜ʖ ͡ᵔ )<span>World</span>"}

  """
  @spec find(String.t, String.t, String.t) :: success() | error()
  def find(bin, selector, delimiter \\ "|") when is_binary(bin) do
    ModestEx.Safe.find(bin, selector, delimiter)
  end

  @doc """
  Serialize html into a valid html string.
  Returns the selected node as a html string.

  ## Examples

    iex> ModestEx.serialize("<div>Hello<span>World")
    {:ok, "<html><head></head><body><div>Hello<span>World</span></div></body></html>"}

  """
  @spec serialize(String.t) :: success() | error()
  def serialize(bin) when is_binary(bin) do
    ModestEx.Safe.serialize(bin)
  end

end
