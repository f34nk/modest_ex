defmodule ClientTest do
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

  test "can be started with an already started cnode" do
    cnode = :"foobar@127.0.0.1"
    {:ok, _state} = Cnode.spawn_cnode(%{
      exec_path: "priv/modest_client",
      cnode: cnode,
      sname: "foobar",
      hostname: "127.0.0.1",
      ready_line: "foobar@127.0.0.1 ready"
    })
    {:ok, pid} = Cnode.start_link(%{
      exec_path: "priv/modest_client",
      cnode: cnode
    })
    {:ok, _} = Cnode.call(pid, {:serialize, "<div>Hello<span>World"})
  end

  test "fails when executable does not activate within spawn_inactive_timeout" do
    assert {:stop, :spawn_inactive_timeout} = Cnode.init(%{
      exec_path: "priv/modest_client",
      spawn_inactive_timeout: 0
    })
  end

  test "fails when connection cannot be established" do
    assert {:stop, :unable_to_establish_connection} = Cnode.init(%{
      exec_path: "priv/modest_client",
      sname: "unconnectable",
      ready_line: "initialising unconnectable@#{Nodex.host()}",
    })
  end

  # test "fails when cnode exits unexpectedly" do
  #   assert {:stop, :cnode_unexpected_exit} = Cnode.init(%{exec_path: "priv/just_exit"})
  # end
end

