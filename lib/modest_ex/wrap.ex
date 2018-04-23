defmodule ModestEx.Wrap do
  @moduledoc false

  def wrap([bin | rest], selector, new_bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    [wrap(bin, selector, new_bin)] ++ wrap(rest, selector, new_bin)
  end

  def wrap([], _, _), do: []

  def wrap(bin, selector, new_bin)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    ModestEx.Safe.Wrap.wrap(bin, selector, new_bin)
  end
end
