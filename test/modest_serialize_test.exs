defmodule ModestSerializeTest do
  use ExUnit.Case
  alias Nodex.Cnode
  doctest Cnode

  setup_all(_) do
    Nodex.Distributed.up
    :ok
  end

  setup(_) do
    # stop slaves that might have not been cleaned up
    Node.list() |> Enum.each(&:slave.stop/1)
    :ok
  end

  test "can parse html from file and serialize its content" do
    content = File.read!("test/fixtures/lorem_ipsum.html")
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, {:serialize, serialized}} = Cnode.call(pid, {:serialize, content})
    assert <<"<-undef>"::utf8>> <> _ = serialized
  end

end