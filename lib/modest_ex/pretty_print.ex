defmodule ModestEx.PrettyPrint do
  @moduledoc false

  def pretty_print([bin | rest]) do
    [pretty_print(bin)] ++ pretty_print(rest)
  end

  def pretty_print([]), do: []

  def pretty_print(bin) when is_bitstring(bin) do
    ModestEx.LexborHelper.not_implemented("pretty_print/1")
  end
end
