defmodule ModestEx.Transform do
  @moduledoc false

  def transform(bin, [instruction|rest]) when is_bitstring(bin) when is_tuple(instruction) when is_list(rest) do
    new_bin = transform(bin, instruction)
    transform(new_bin, rest)
  end

  def transform(bin, {:append, selector, new_html}) when is_bitstring(bin) do
    ModestEx.append(bin, selector, new_html)
  end

  def transform(bin, {:remove, selector}) when is_bitstring(bin) do
    ModestEx.remove(bin, selector)
  end

  def transform(bin, {:set_attribute, selector, key, value}) when is_bitstring(bin) do
    ModestEx.set_attribute(bin, selector, key, value)
  end

  def transform(bin, {:set_text, selector, new_text}) when is_bitstring(bin) do
    ModestEx.set_text(bin, selector, new_text)
  end
  
  def transform(bin, _), do: bin

end