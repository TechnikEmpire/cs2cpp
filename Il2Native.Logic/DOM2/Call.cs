﻿namespace Il2Native.Logic.DOM2
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;

    using Microsoft.CodeAnalysis;
    using Microsoft.CodeAnalysis.CSharp;
    using Microsoft.CodeAnalysis.CSharp.Symbols;

    public class Call : Expression
    {
        private readonly IList<Expression> _arguments = new List<Expression>();

        public override Kinds Kind
        {
            get { return Kinds.Call; }
        }

        public bool IsCallingConstructor
        {
            get
            {
                return this.Method.MethodKind == MethodKind.Constructor;
            }
        }

        public IMethodSymbol Method { get; set; }

        public Expression ReceiverOpt { get; set; }

        public IList<Expression> Arguments
        {
            get
            {
                return this._arguments;
            }
        }

        internal static void WriteCallArguments(IEnumerable<Expression> arguments, IEnumerable<IParameterSymbol> parameterSymbols, CCodeWriterBase c)
        {
            c.TextSpan("(");
            var anyArgs = false;

            var paramEnum = parameterSymbols != null ? parameterSymbols.GetEnumerator() : null;
            foreach (var expression in arguments)
            {
                var hasParameter = false;
                if (paramEnum != null)
                {
                    hasParameter = paramEnum.MoveNext();
                }

                if (anyArgs)
                {
                    c.TextSpan(",");
                    c.WhiteSpace();
                }

                PreprocessParameter(expression, hasParameter ? paramEnum.Current : null).WriteTo(c);
                anyArgs = true;
            }

            c.TextSpan(")");
        }

        private static Expression PreprocessParameter(Expression expression, IParameterSymbol parameter)
        {
            if (parameter == null)
            {
                return expression;
            }

            var parameterType = parameter.Type;
            if (parameterType == null)
            {
                return expression;
            }

            var effectiveExpression = expression;

            var typeDestination = parameterType;
            if (typeDestination.IsReferenceType)
            {
                var literal = expression as Literal;
                if (literal != null && literal.Value.IsNull)
                {
                    effectiveExpression = new Conversion
                    {
                        Type = typeDestination,
                        Operand = effectiveExpression
                    };
                }
            }

            if (typeDestination.IsValueType && expression is ThisReference)
            {
                effectiveExpression = new PointerIndirectionOperator { Operand = expression };
            }

            if (expression.IsStaticWrapperCall())
            {
                effectiveExpression = new Cast
                {
                    Type = typeDestination,
                    Operand = effectiveExpression,
                    Reference = parameter.RefKind.HasFlag(RefKind.Ref),
                    CCast = true,
                    UseEnumUnderlyingType = true,
                };
            }

            return effectiveExpression;
        }

        internal void Parse(BoundCall boundCall)
        {
            base.Parse(boundCall);
            this.Method = boundCall.Method;
            if (boundCall.ReceiverOpt != null)
            {
                this.ReceiverOpt = Deserialize(boundCall.ReceiverOpt) as Expression;
                // special case to avoid calling (*xxx).method() and replace with xxx->method();
                var pointerIndirectionOperator = this.ReceiverOpt as PointerIndirectionOperator;
                if (pointerIndirectionOperator != null)
                {
                    this.ReceiverOpt = pointerIndirectionOperator.Operand;
                    this.ReceiverOpt.IsReference = true;
                }
            }

            foreach (var expression in boundCall.Arguments)
            {
                var argument = Deserialize(expression) as Expression;
                Debug.Assert(argument != null);
                this._arguments.Add(argument);
            }
        }

        internal override void WriteTo(CCodeWriterBase c)
        {
            if (this.Method.IsStaticMethod())
            {
                c.WriteTypeFullName(this.Method.ContainingType);
                c.TextSpan("::");
                c.WriteMethodName(this.Method, addTemplate: true);
            }
            else
            {
                var receiverOpt = this.ReceiverOpt;
                if (receiverOpt != null)
                {
                    receiverOpt = this.PrepareMethodReceiver(receiverOpt, this.Method);
                    c.WriteAccess(receiverOpt);
                }

                c.WriteMethodName(this.Method, addTemplate: true/*, methodSymbolForName: explicitMethod*/);
            }

            WriteCallArguments(this._arguments, this.Method != null ? this.Method.Parameters : (IEnumerable<IParameterSymbol>)null, c);
        }

        private Expression PrepareMethodReceiver(Expression receiverOpt, IMethodSymbol methodSymbol)
        {
            var effectiveReceiverOpt = receiverOpt;

            if (effectiveReceiverOpt.Kind == Kinds.ThisReference 
                && methodSymbol.MethodKind == MethodKind.Constructor
                && receiverOpt.Type != methodSymbol.ReceiverType)
            {
                effectiveReceiverOpt = new BaseReference { Type = this.Method.ReceiverType };
            }

            if (!effectiveReceiverOpt.IsReference &&
                (effectiveReceiverOpt.Type.IsPrimitiveValueType() || effectiveReceiverOpt.Type.TypeKind == TypeKind.Enum))
            {
                effectiveReceiverOpt = new Cast { Operand = effectiveReceiverOpt, Type = effectiveReceiverOpt.Type, ClassCast = true };
            }
            
            if (effectiveReceiverOpt.Type.TypeKind == TypeKind.TypeParameter && this.Method.ReceiverType != effectiveReceiverOpt.Type)
            {
                ////var constrained = ((ITypeParameterSymbol)receiverOpt.Type).ConstraintTypes;
                ////foreach (var constrainedType in constrained)
                ////{
                ////    receiverOpt = new Cast
                ////    {
                ////        Constrained = true,
                ////        Operand = receiverOpt,
                ////        Type = constrainedType
                ////    };
                ////}
                effectiveReceiverOpt = new Cast
                {
                    Constrained = true,
                    Operand = effectiveReceiverOpt,
                    Type = this.Method.ReceiverType
                };
            }

            return effectiveReceiverOpt;
        }
    }
}
