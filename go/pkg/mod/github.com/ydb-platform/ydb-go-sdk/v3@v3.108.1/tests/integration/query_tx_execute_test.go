//go:build integration
// +build integration

package integration

import (
	"context"
	"errors"
	"fmt"
	"testing"

	"github.com/stretchr/testify/require"
	"github.com/ydb-platform/ydb-go-genproto/protos/Ydb"

	"github.com/ydb-platform/ydb-go-sdk/v3"
	internalQuery "github.com/ydb-platform/ydb-go-sdk/v3/internal/query"
	baseTx "github.com/ydb-platform/ydb-go-sdk/v3/internal/tx"
	"github.com/ydb-platform/ydb-go-sdk/v3/query"
)

func TestQueryTxExecute(t *testing.T) {
	scope := newScope(t)

	t.Run("Default", func(t *testing.T) {
		var (
			columnNames []string
			columnTypes []string
		)
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			res, err := tx.Query(ctx, "SELECT 1 AS col1")
			if err != nil {
				return err
			}
			rs, err := res.NextResultSet(ctx)
			if err != nil {
				return err
			}
			columnNames = rs.Columns()
			for _, t := range rs.ColumnTypes() {
				columnTypes = append(columnTypes, t.Yql())
			}
			row, err := rs.NextRow(ctx)
			if err != nil {
				return err
			}
			var col1 int
			err = row.ScanNamed(query.Named("col1", &col1))
			if err != nil {
				return err
			}
			err = tx.Exec(ctx, "SELECT 1")
			if err != nil {
				return err
			}
			_ = res.Close(ctx)

			return nil
		}, query.WithIdempotent())
		require.NoError(t, err)
		require.Equal(t, []string{"col1"}, columnNames)
		require.Equal(t, []string{"Int32"}, columnTypes)
	})
	t.Run("WithLazyTx", func(t *testing.T) {
		var (
			columnNames []string
			columnTypes []string
		)
		err := scope.Driver(ydb.WithLazyTx(true)).Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			if tx.ID() != baseTx.LazyTxID {
				return errors.New("transaction is not lazy")
			}
			res, err := tx.Query(ctx, "SELECT 1 AS col1")
			if err != nil {
				return err
			}
			if tx.ID() == baseTx.LazyTxID {
				return errors.New("transaction is lazy yet")
			}
			rs, err := res.NextResultSet(ctx)
			if err != nil {
				return err
			}
			columnNames = rs.Columns()
			for _, t := range rs.ColumnTypes() {
				columnTypes = append(columnTypes, t.Yql())
			}
			row, err := rs.NextRow(ctx)
			if err != nil {
				return err
			}
			var col1 int
			err = row.ScanNamed(query.Named("col1", &col1))
			if err != nil {
				return err
			}
			err = tx.Exec(ctx, "SELECT 1")
			if err != nil {
				return err
			}
			_ = res.Close(ctx)

			return nil
		}, query.WithIdempotent())
		require.NoError(t, err)
		require.Equal(t, []string{"col1"}, columnNames)
		require.Equal(t, []string{"Int32"}, columnTypes)
	})
	t.Run("SerializableReadWrite", func(t *testing.T) {
		var (
			columnNames []string
			columnTypes []string
		)
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			res, err := tx.Query(ctx, "SELECT 1 AS col1")
			if err != nil {
				return err
			}
			rs, err := res.NextResultSet(ctx)
			if err != nil {
				return err
			}
			columnNames = rs.Columns()
			columnTypes = columnTypes[:0]
			for _, t := range rs.ColumnTypes() {
				columnTypes = append(columnTypes, t.Yql())
			}
			row, err := rs.NextRow(ctx)
			if err != nil {
				return err
			}
			var col1 int
			err = row.ScanNamed(query.Named("col1", &col1))
			if err != nil {
				return err
			}
			return nil
		}, query.WithIdempotent(), query.WithTxSettings(query.TxSettings(query.WithSerializableReadWrite())))
		require.NoError(t, err)
		require.Equal(t, []string{"col1"}, columnNames)
		require.Equal(t, []string{"Int32"}, columnTypes)
	})
	t.Run("SnapshotReadOnly", func(t *testing.T) {
		var (
			columnNames []string
			columnTypes []string
		)
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			res, err := tx.Query(ctx, "SELECT 1 AS col1")
			if err != nil {
				return err
			}
			rs, err := res.NextResultSet(ctx)
			if err != nil {
				return err
			}
			columnNames = rs.Columns()
			columnTypes = columnTypes[:0]
			for _, t := range rs.ColumnTypes() {
				columnTypes = append(columnTypes, t.Yql())
			}
			row, err := rs.NextRow(ctx)
			if err != nil {
				return err
			}
			var col1 int
			err = row.ScanNamed(query.Named("col1", &col1))
			if err != nil {
				return err
			}
			return nil
		}, query.WithIdempotent(), query.WithTxSettings(query.TxSettings(query.WithSnapshotReadOnly())))
		require.NoError(t, err)
		require.Equal(t, []string{"col1"}, columnNames)
		require.Equal(t, []string{"Int32"}, columnTypes)
	})
	t.Run("OnlineReadOnly", func(t *testing.T) {
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			res, err := tx.Query(ctx, "SELECT 1 AS col1")
			if err != nil {
				return err
			}
			rs, err := res.NextResultSet(ctx)
			if err != nil {
				return err
			}
			row, err := rs.NextRow(ctx)
			if err != nil {
				return err
			}
			var col1 int
			err = row.ScanNamed(query.Named("col1", &col1))
			if err != nil {
				return err
			}
			return nil
		}, query.WithIdempotent(), query.WithTxSettings(query.TxSettings(query.WithOnlineReadOnly())))
		require.True(t, ydb.IsOperationError(err, Ydb.StatusIds_BAD_REQUEST))
	})
	t.Run("StaleReadOnly", func(t *testing.T) {
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			res, err := tx.Query(ctx, "SELECT 1 AS col1")
			if err != nil {
				return err
			}
			rs, err := res.NextResultSet(ctx)
			if err != nil {
				return err
			}
			row, err := rs.NextRow(ctx)
			if err != nil {
				return err
			}
			var col1 int
			err = row.ScanNamed(query.Named("col1", &col1))
			if err != nil {
				return err
			}
			return nil
		}, query.WithIdempotent(), query.WithTxSettings(query.TxSettings(query.WithStaleReadOnly())))
		require.True(t, ydb.IsOperationError(err, Ydb.StatusIds_BAD_REQUEST))
	})
	t.Run("ErrOptionNotForTxExecute", func(t *testing.T) {
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			err = tx.Exec(ctx, "SELECT 1 AS col1",
				query.WithTxControl(query.TxControl(query.BeginTx(query.WithOnlineReadOnly()))),
			)
			if err != nil {
				return err
			}

			return nil
		}, query.WithIdempotent())
		require.Error(t, err)
		t.Logf("err: %s", err.Error())
		require.ErrorIs(t, err, internalQuery.ErrOptionNotForTxExecute)
	})
}

func TestQueryLazyTxExecute(t *testing.T) {
	scope := newScope(t)

	var (
		columnNames []string
		columnTypes []string
	)
	t.Run("Default", func(t *testing.T) {
		err := scope.DriverWithLogs(ydb.WithLazyTx(true)).Query().DoTx(
			scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
				if tx.ID() != baseTx.LazyTxID {
					return errors.New("transaction is not lazy")
				}
				res, err := tx.Query(ctx, "SELECT 1 AS col1")
				if err != nil {
					return err
				}
				if tx.ID() == baseTx.LazyTxID {
					return errors.New("transaction is lazy yet")
				}
				rs, err := res.NextResultSet(ctx)
				if err != nil {
					return err
				}
				columnNames = rs.Columns()
				for _, t := range rs.ColumnTypes() {
					columnTypes = append(columnTypes, t.Yql())
				}
				row, err := rs.NextRow(ctx)
				if err != nil {
					return err
				}
				var col1 int
				err = row.ScanNamed(query.Named("col1", &col1))
				if err != nil {
					return err
				}
				err = tx.Exec(ctx, "SELECT 1")
				if err != nil {
					return err
				}
				_ = res.Close(ctx)

				return nil
			}, query.WithIdempotent(),
		)
		require.NoError(t, err)
		require.Equal(t, []string{"col1"}, columnNames)
		require.Equal(t, []string{"Int32"}, columnTypes)
	})
	t.Run("SerializableReadWrite", func(t *testing.T) {
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			if tx.ID() != baseTx.LazyTxID {
				return errors.New("transaction is not lazy")
			}
			res, err := tx.Query(ctx, "SELECT 1 AS col1")
			if err != nil {
				return err
			}
			if tx.ID() == baseTx.LazyTxID {
				return errors.New("transaction is lazy yet")
			}
			rs, err := res.NextResultSet(ctx)
			if err != nil {
				return err
			}
			columnNames = rs.Columns()
			columnTypes = columnTypes[:0]
			for _, t := range rs.ColumnTypes() {
				columnTypes = append(columnTypes, t.Yql())
			}
			row, err := rs.NextRow(ctx)
			if err != nil {
				return err
			}
			var col1 int
			err = row.ScanNamed(query.Named("col1", &col1))
			if err != nil {
				return err
			}
			return nil
		}, query.WithIdempotent(), query.WithTxSettings(query.TxSettings(query.WithSerializableReadWrite())))
		require.NoError(t, err)
		require.Equal(t, []string{"col1"}, columnNames)
		require.Equal(t, []string{"Int32"}, columnTypes)
	})
	t.Run("SnapshotReadOnly", func(t *testing.T) {
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			if tx.ID() != baseTx.LazyTxID {
				return errors.New("transaction is not lazy")
			}
			res, err := tx.Query(ctx, "SELECT 1 AS col1")
			if err != nil {
				return err
			}
			if tx.ID() == baseTx.LazyTxID {
				return errors.New("transaction is lazy yet")
			}
			rs, err := res.NextResultSet(ctx)
			if err != nil {
				return err
			}
			columnNames = rs.Columns()
			columnTypes = columnTypes[:0]
			for _, t := range rs.ColumnTypes() {
				columnTypes = append(columnTypes, t.Yql())
			}
			row, err := rs.NextRow(ctx)
			if err != nil {
				return err
			}
			var col1 int
			err = row.ScanNamed(query.Named("col1", &col1))
			if err != nil {
				return err
			}
			return nil
		}, query.WithIdempotent(), query.WithTxSettings(query.TxSettings(query.WithSnapshotReadOnly())))
		require.NoError(t, err)
		require.Equal(t, []string{"col1"}, columnNames)
		require.Equal(t, []string{"Int32"}, columnTypes)
	})
	t.Run("OnlineReadOnly", func(t *testing.T) {
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			if tx.ID() != baseTx.LazyTxID {
				return errors.New("transaction is not lazy")
			}
			res, err := tx.Query(ctx, "SELECT 1 AS col1")
			if err != nil {
				return err
			}
			if tx.ID() == baseTx.LazyTxID {
				return errors.New("transaction is lazy yet")
			}
			rs, err := res.NextResultSet(ctx)
			if err != nil {
				return err
			}
			columnNames = rs.Columns()
			columnTypes = columnTypes[:0]
			for _, t := range rs.ColumnTypes() {
				columnTypes = append(columnTypes, t.Yql())
			}
			row, err := rs.NextRow(ctx)
			if err != nil {
				return err
			}
			var col1 int
			err = row.ScanNamed(query.Named("col1", &col1))
			if err != nil {
				return err
			}
			return nil
		}, query.WithIdempotent(), query.WithTxSettings(query.TxSettings(query.WithOnlineReadOnly())))
		require.NoError(t, err)
	})
	t.Run("StaleReadOnly", func(t *testing.T) {
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			if tx.ID() != baseTx.LazyTxID {
				return errors.New("transaction is not lazy")
			}
			res, err := tx.Query(ctx, "SELECT 1 AS col1")
			if err != nil {
				return err
			}
			if tx.ID() == baseTx.LazyTxID {
				return errors.New("transaction is lazy yet")
			}
			rs, err := res.NextResultSet(ctx)
			if err != nil {
				return err
			}
			columnNames = rs.Columns()
			columnTypes = columnTypes[:0]
			for _, t := range rs.ColumnTypes() {
				columnTypes = append(columnTypes, t.Yql())
			}
			row, err := rs.NextRow(ctx)
			if err != nil {
				return err
			}
			var col1 int
			err = row.ScanNamed(query.Named("col1", &col1))
			if err != nil {
				return err
			}
			return nil
		}, query.WithIdempotent(), query.WithTxSettings(query.TxSettings(query.WithStaleReadOnly())))
		require.NoError(t, err)
	})
	t.Run("ErrOptionNotForTxExecute", func(t *testing.T) {
		err := scope.DriverWithLogs().Query().DoTx(scope.Ctx, func(ctx context.Context, tx query.TxActor) (err error) {
			if tx.ID() != baseTx.LazyTxID {
				return errors.New("transaction is not lazy")
			}
			err = tx.Exec(ctx, "SELECT 1 AS col1",
				query.WithTxControl(query.TxControl(query.BeginTx(query.WithOnlineReadOnly()))),
			)
			if err != nil {
				return err
			}

			return nil
		}, query.WithIdempotent())
		require.Error(t, err)
		t.Logf("err: %s", err.Error())
		require.ErrorIs(t, err, internalQuery.ErrOptionNotForTxExecute)
	})
}

func TestQueryWithCommitTxFlag(t *testing.T) {
	scope := newScope(t)
	var count uint64
	err := scope.DriverWithLogs().Query().Do(scope.Ctx, func(ctx context.Context, s query.Session) error {
		tableName := scope.TablePath()
		tx, err := s.Begin(ctx, query.TxSettings(query.WithDefaultTxMode()))
		if err != nil {
			return fmt.Errorf("failed start transaction: %w", err)
		}
		q := fmt.Sprintf("UPSERT INTO `%v` (id, val) VALUES(1, \"2\")", tableName)
		err = tx.Exec(ctx, q, query.WithCommit())
		if err != nil {
			return fmt.Errorf("failed execute insert: %w", err)
		}

		// read row within other (implicit) transaction
		q2 := fmt.Sprintf("SELECT COUNT(*) FROM `%v`", tableName)
		r, err := s.Query(ctx, q2)
		if err != nil {
			return fmt.Errorf("failed query: %w", err)
		}

		rs, err := r.NextResultSet(ctx)
		if err != nil {
			return fmt.Errorf("failed iterate to next result set: %w", err)
		}

		row, err := rs.NextRow(ctx)
		if err != nil {
			return fmt.Errorf("failed iterate to next row: %w", err)
		}

		if err = row.Scan(&count); err != nil {
			return fmt.Errorf("failed scan row: %w", err)
		}
		return nil
	})
	require.NoError(t, err)
	require.Equal(t, uint64(1), count)
}
