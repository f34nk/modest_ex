defmodule ModestEx.Append do
  @moduledoc false

  def append([bin | rest], selector, new_bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    [append(bin, selector, new_bin)] ++ append(rest, selector, new_bin)
  end

  def append([], _, _), do: []

  def append(bin, selector, new_bin)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    ModestEx.Safe.Append.append(bin, selector, new_bin)
  end
end
