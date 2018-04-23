defmodule ModestEx.Prepend do
  @moduledoc false

  def prepend([bin | rest], selector, new_bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    [prepend(bin, selector, new_bin)] ++ prepend(rest, selector, new_bin)
  end

  def prepend([], _, _), do: []

  def prepend(bin, selector, new_bin)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    ModestEx.Safe.Prepend.prepend(bin, selector, new_bin)
  end
end
