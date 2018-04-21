defmodule ModestEx.Safe.Text do
  @moduledoc false
  
  def get_text(bin) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:get_text, bin <> "\0", ModestEx.delimiter() <> "\0"}) do
      {:ok, {:get_text, result}} -> ModestEx.resolve(result)
      _ -> {:error, bin}
    end
  end

  def get_text(bin, selector) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:get_text, bin <> "\0", selector <> "\0", ModestEx.delimiter() <> "\0"}) do
      {:ok, {:get_text, result}} -> ModestEx.resolve(result)
      _ -> {:error, bin}
    end
  end

  def set_text(bin, selector, text) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:set_text, bin <> "\0", selector <> "\0", text <> "\0", ModestEx.scope() <> "\0"}) do
      {:ok, {:set_text, result}} -> ModestEx.resolve(result)
      _ -> {:error, bin}
    end
  end
  
end