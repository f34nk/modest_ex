defmodule ModestEx.InsertAfter do
  @moduledoc false

  def insert_after([bin | rest], selector, new_bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    [insert_after(bin, selector, new_bin)] ++ insert_after(rest, selector, new_bin)
  end

  def insert_after([], _, _), do: []

  def insert_after(bin, selector, new_bin)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    # ModestEx.Safe.InsertAfter.insert_after(bin, selector, new_bin)
    ModestEx.LexborHelper.not_implemented("insert_after/3")
  end
end
