defmodule ModestEx.Safe.Attribute do
  @moduledoc false
  
  def get_attribute(bin, key) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:get_attribute, bin <> "\0", key <> "\0", ModestEx.delimiter() <> "\0"}) do
      {:ok, {:get_attribute, result}} -> ModestEx.split(result)
      _ -> {:error, bin}
    end
  end

  def get_attribute(bin, selector, key) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:get_attribute, bin <> "\0", selector <> "\0", key <> "\0", ModestEx.delimiter() <> "\0"}) do
      {:ok, {:get_attribute, result}} -> ModestEx.split(result)
      _ -> {:error, bin}
    end
  end

  def set_attribute(bin, selector, key, value) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:set_attribute, bin <> "\0", selector <> "\0", key <> "\0", value <> "\0", ModestEx.scope() <> "\0"}) do
      {:ok, {:set_attribute, result}} -> result
      _ -> {:error, bin}
    end
  end
  
end