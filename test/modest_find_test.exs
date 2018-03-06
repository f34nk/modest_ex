defmodule ModestFindTest do
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

  test "can find node with CSS selector" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, {:find, reply}} = Cnode.call(pid, {:find, "<p><a>Hello</a> World</p>", "p a", "|", "body"})
    assert reply == "<a>Hello</a>"
  end

end

